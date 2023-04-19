//
// Created by sorana on 1/14/2023.
//

#include "../include/ConnectedUser.h"

ConnectedUser::ConnectedUser(const User &connectingUser)
    : m_connectedUser(connectingUser)
    , m_recomService(connectingUser.GetId()){}

User &ConnectedUser::GetUser(){
    return m_connectedUser;
}

UserRecomService &ConnectedUser::GetRecomService() {
    return m_recomService;
}

void ConnectedUser::SetUserRecomServiceId(const uint16_t& userId)
{
    m_recomService.SetCurrentUserId(userId);
}
