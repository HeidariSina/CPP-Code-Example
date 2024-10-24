#include "server.h"
#include "client.h"

Server::Server() : clients{}
{
}
std::shared_ptr<Client> Server::add_client(std::string id)
{
    std::shared_ptr<Client> cl(nullptr);
    bool flag{true};
    auto it{clients.begin()};
    while (it != clients.end())
    {
        if (it->first->get_id() == id)
        {
            flag = false;
            break;
        }
        it++;
    }
    if (flag == true)
    {
        auto clie{Client(id, *this)};
        cl = std::make_shared<Client>(clie);
        clients.insert({cl, 5.0});
        return cl;
    }
    else
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<> distr(1000, 9999);

        int a = distr(eng);
        std::string final{}, sat{std::to_string(a)};

        final = id + sat;
        auto clie{Client(final, *this)};
        cl = std::make_shared<Client>(clie);
        clients.insert({cl, 5.0});
        return cl;
    }
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    auto it{clients.begin()};
    while (it != clients.end())
    {
        if (it->first->get_id() == id)
        {
            return it->first;
        }
        it++;
    }
    return nullptr;
}

double Server::get_wallet(std::string id)
{
    auto it{clients.begin()};
    while (it != clients.end())
    {
        if (it->first->get_id() == id)
        {
            return it->second;
        }
        it++;
    }
    return 0;
}
bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value)
{
    std::string inpu{trx};
    size_t found{inpu.find("-")};
    if (found == std::string::npos)
        throw std::runtime_error("1st - not found");

    size_t found2{inpu.find("-", found + 1)};
    if (found2 == std::string::npos)
        throw std::runtime_error("2nd - not found");

    sender = trx.substr(0, found);
    receiver = trx.substr(found + 1, found2 - found - 1);
    value = std::stod(trx.substr(found2 + 1));

    return true;
}
bool Server::add_pending_trx(std::string trx, std::string signature)
{
    std::string sender{}, receiver{};
    double value;

    parse_trx(trx, sender, receiver, value);
    double m{get_wallet(sender)};

    auto temp1 = get_client(sender);
    auto temp2 = temp1->get_publickey();
    bool authentic = crypto::verifySignature(temp2, trx, signature);

    if (value > m)
        return false;
    if (get_client(sender) == nullptr || get_client(receiver) == nullptr || authentic == false)
        return false;
    pending_trxs.push_back(trx);
    return true;
}
size_t Server::mine()
{
    std::string mempool{}, mem2{}, sender{}, reciver{}, hash{};
    double val{};
    size_t non{};
    for (auto m : pending_trxs)
    {
        mempool += m;
    }
    int size = pending_trxs.size();
    int g{0};
    while (1)
    {
        auto m = pending_trxs[g];
        parse_trx(m, sender, reciver, val);
        auto cli = get_client(sender);
        auto nounce = cli->generate_nonce();
        mem2 = mempool + std::to_string(nounce);
        hash = crypto::sha256(mem2);
        if (hash.substr(0, 10).find("000") != std::string::npos)
        {
            clients[cli] = clients[cli] + 6.25;
            std::cout << "the winner is : " << sender << std::endl;
            non = nounce;
            break;
        }
        g++;
        if (g == size)
            g = 0;
    }
    for (auto m : pending_trxs)
    {
        parse_trx(m, sender, reciver, val);
        auto cli{get_client(sender)};
        auto res{get_client(reciver)};
        clients[cli] = clients[cli] - val;
        clients[res] = clients[res] + val;
    }
    pending_trxs.clear();
    return non;
}