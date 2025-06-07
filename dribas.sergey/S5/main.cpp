#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

void parseGpxFile(const std::string& filename) {
    pt::ptree tree;

    // Читаем XML-файл в property_tree
    pt::read_xml(filename, tree);

    // Парсим основные данные трека
    std::string name = tree.get<std::string>("trk.name", "Unnamed Track");
    std::string type = tree.get<std::string>("trk.type", "Unknown");

    std::cout << "Track Name: " << name << std::endl;
    std::cout << "Activity Type: " << type << std::endl;

    // Парсим трекпоинты
    BOOST_FOREACH(const pt::ptree::value_type &trkpt, tree.get_child("trk.trkseg")) {
        if (trkpt.first == "trkpt") {
            // Координаты
            double lat = trkpt.second.get<double>("<xmlattr>.lat");
            double lon = trkpt.second.get<double>("<xmlattr>.lon");

            // Высота
            double ele = trkpt.second.get<double>("ele", 0.0);

            // Время
            std::string time = trkpt.second.get<std::string>("time", "");

            // Расширения (HR, Cadence)
            int hr = 0;
            int cad = 0;
            try {
                hr = trkpt.second.get<int>("extensions.ns3:TrackPointExtension.ns3:hr", 0);
                cad = trkpt.second.get<int>("extensions.ns3:TrackPointExtension.ns3:cad", 0);
            } catch (...) {
                // Если нет расширений, игнорируем
            }

            // Выводим информацию о трекпоинте
            std::cout << "\nTrackpoint:" << std::endl;
            std::cout << "  Coordinates: " << lat << ", " << lon << std::endl;
            std::cout << "  Elevation: " << ele << " m" << std::endl;
            std::cout << "  Time: " << time << std::endl;
            std::cout << "  HR: " << hr << " bpm" << std::endl;
            std::cout << "  Cadence: " << cad << " rpm" << std::endl;
        }
    }
}

int main() {
    try {
        parseGpxFile("1.gpx"); // Замените на путь к вашему GPX-файлу
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
