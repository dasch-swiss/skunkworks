//
// Created by Ivan Subotic on 27/11/2020.
//

#include "helpers/uuid.h"
#include "user.h"

dsp::User::User(std::string username,
                std::string email,
                std::string password,
                std::string token,
                std::string given_name,
                std::string family_name,
                std::string status,
                std::string lang):
                username_(username),
                email_(email),
                password_(password),
                token_(token),
                given_name(given_name),
                family_name(family_name),
                status_(status),
                lang_(lang)
                {
  id_ = uuid::generate_uuid_v4();

}
