#include <map>
#include <memory>
#include <vector>
#include <random>
#include "client.h"
#include "server.h"

Client::Client(std::string id, const Server &server) : server(&server), id(id)
{
    public_key = {};
    private_key = {};
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id()
{
    return id;
}

std::string Client::get_publickey() const
{
    return public_key;
}

double Client::get_wallet()
{
    auto ser{*server};
    double money{ser.get_wallet(id)};
    return money;
}

std::string Client::sign(std::string txt) const
{

    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value)
{
    std::string trx{id + "-" + receiver + "-" + std::to_string(value)}, sig{};
    auto ser = *server;
    sig = sign(trx);
    bool answer1{ser.add_pending_trx(trx, sig)};
    return (answer1);
}

size_t Client::generate_nonce()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution distr(0, 10000);
    size_t temp{static_cast<long unsigned int>(distr(eng))};
    return temp;
}