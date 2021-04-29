#pragma once

#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Client.hpp"
#include <SFML/Network.hpp>
#include "NameTag.hpp"
 
class OnlinePlayer : public RottEngine::Entity {
public:
    OnlinePlayer();
    virtual ~OnlinePlayer();
    void setNickname(const std::string& nickname);
    void setPosition(float x, float y);
    std::string getNickname() const;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    NameTag m_nametag;
    std::string m_nickname;
};