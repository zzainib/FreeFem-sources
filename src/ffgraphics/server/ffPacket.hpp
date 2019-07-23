#ifndef FF_PACKET_HPP
#define FF_PACKET_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "RNM.hpp"

class ffPacket {
    public:

        inline std::string& GetHeader() const { return m_Header; }

        inline std::vector<uint8_t>& GetPacketData() const { return m_Data; }

        ostream& operator<<(ostream& os, const ffPacket& packet) {
            os << "Header :\n" << packet.GetHeader() << "\n";
            const std::vector<uint8_t>& tmp = packet.GetPacketData();
            for (int i = 0; i < tmp.size(); ++i) {
                os << tmp[i];
            }
            os << "\n";
        }

    private:

        void GetPacketHeader(int size)
        {
            json j;
            std::string tmp;

            j["Size"] = size;
            j["Version"] = "FreeFem++ Header 0.1";
            j["Padding"] = "";
            tmp = j.dump();
            if (tmp.length() < 66) {
                std::string padding = "";
                for (size_t i = 0; i < 66 - tmp.length(); ++i)
                    padding.push_back('a');
                j["Padding"] = padding;
            }
            m_Header = j.dump();
        }

        std::string m_Header;
        std::vector<uint8_t> m_Data;

};

#endif // FF_PACKET_HPP