#include "LocalPlayer.hpp"
#include "Engine/Networking/Packets.hpp"

LocalPlayer::LocalPlayer(RottEngine::Client* p_client) : PlayerBase(PlayerType::LOCAL), mp_client(p_client) {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/player.png"));
    m_sprite.setScale(3,3);
    m_nametag.setName(p_client->getNickname().c_str(), sf::Color::Cyan);
    RottEngine::Utils::center(&m_sprite);

    setItem(new Sword((PlayerBase*)this));
}

LocalPlayer::~LocalPlayer(){
}

void LocalPlayer::update(const sf::Time& dt){
    if(!m_can_move){
        return;
    }

    sf::Vector2f move_dir;

    float speed = PLAYER_MOVE_SPEED * dt.asSeconds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ move_dir.y -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ move_dir.y += speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ move_dir.x -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ move_dir.x += speed; }

    m_sprite.move(move_dir);

    sf::Vector2f pos = m_sprite.getPosition();
    m_nametag.update();

    if(mp_held_item != nullptr){
        mp_held_item->update(dt);
    }
}

void LocalPlayer::tick(){
    if(!m_can_move){
        return;
    }

    // If the position has changed, send the player moved packet to the server
    sf::Vector2f curr_pos = m_sprite.getPosition();

    if(m_previous_pos != curr_pos){
        sf::Packet player_moved_packed;
        player_moved_packed << sf::Uint8(CLIENT_PLAYER_MOVED) << curr_pos.x << curr_pos.y;

        mp_client->sendPacket(player_moved_packed);
    }

    m_previous_pos = curr_pos;
}

void LocalPlayer::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
    m_nametag.draw(window);

    if(mp_held_item != nullptr){
        mp_held_item->draw(window);
    }
}

RottEngine::Client* LocalPlayer::getClient() const {
    return mp_client;
}

void LocalPlayer::setCanMove(bool value){
    m_can_move = value;
}
