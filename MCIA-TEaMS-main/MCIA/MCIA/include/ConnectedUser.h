//
// Created by sorana on 1/14/2023.
//

#ifndef MCIA_CONNECTEDUSER_H
#define MCIA_CONNECTEDUSER_H
#include "User.h"
#include "UserRecomService.h"

class ConnectedUser {
public:
    explicit ConnectedUser(const User &connectingUser);

    User &GetUser();
    UserRecomService &GetRecomService();
    void SetUserRecomServiceId(const uint16_t& userId);

private:
    User m_connectedUser;
    UserRecomService m_recomService;
};


#endif //MCIA_CONNECTEDUSER_H
