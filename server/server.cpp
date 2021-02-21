#include <SFML/Network.hpp>

void update()
{

}

int main()
{
    sf::UdpSocket socket;

    socket.bind(8080);

    while(1)
    {
        sf::IpAddress add;
        uint16_t port;
        sf::Packet recPacket;
        
        socket.receive(recPacket, add, port);

    }

    return 0;
}