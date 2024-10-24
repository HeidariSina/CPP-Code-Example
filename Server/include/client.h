#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <random>
#include <map>
#include <memory>
#include <string>
#include "crypto.h"

class Server;

class Client
{
public:
    Client(std::string id, const Server &server);
    std::string get_id();
    std::string get_publickey() const;
    double get_wallet();
    std::string sign(std::string txt) const;
    bool transfer_money(std::string receiver, double value);
    size_t generate_nonce();

private:
    Server const *const server;
    const std::string id;
    std::string public_key;
    std::string private_key;
};

inline void show_wallets(const Server &server)
{
    std::map<std::shared_ptr<Client>, double> *cli{(std::map<std::shared_ptr<Client>, double> *)&server};
    std::cout << std::string(20, '*') << std::endl;
    for (auto it = cli->begin(); it != cli->end(); it++)
    {
        std::cout << it->first->get_id() << " : " << it->second << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}
#endif // CLIENT_H