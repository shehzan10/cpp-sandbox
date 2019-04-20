#include <glm/glm.hpp>
#include <json.hpp>

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char* argv[])
{
    std::string inputFile(argv[1]);
    std::string outputFile = inputFile;
    outputFile.replace(inputFile.size() - 4, 4, "-Fixed.gml");

    std::ifstream ifs(inputFile, std::fstream::in);
    std::ofstream ofs(outputFile, std::fstream::out);

    size_t lineNo = 1;
    std::regex bridgeExpression("^\\s*</?brid:Bridge.+");
    std::regex outerBridgeConstructionExpression("^\\s*</?brid:outerBridgeConstruction.+");
    std::regex outerBrideInstallationExpression("^\\s*</?brid:outerBridgeInstallation.+");
    std::regex bridgeConstructionElementExpression("^\\s*</?brid:BridgeConstructionElement.+");
    std::regex bridgeLod2GeometryExpression("^\\s*</?brid:lod2Geometry.+");
    std::regex bridgeWallSurfaceExpression("^\\s*</?brid:WallSurface.+");
    std::regex bridgeGroundSurfaceExpression("^\\s*</?brid:GroundSurface.+");
    std::regex bridgeOuterCeilingSurfaceExpression("^\\s*</?brid:OuterCeilingSurface.+");
    std::regex bridgeLod2MultiSurfaceExpression("^\\s*</?brid:lod2MultiSurface.+");
    std::regex bridgeOuterFloorSurfaceExpression("^\\s*</?brid:OuterFloorSurface.+");
    std::regex bridgeBoundedByExpression("^\\s*</?brid:boundedBy.+");
    std::regex polygonExpression("^\\s*<gml:Polygon>$");
    std::regex bridgeLod2SolidOpenExpression("^\\s*<brid:lod2Solid>");
    std::regex bridgeLod2SolidCloseExpression("^\\s*</brid:lod2Solid>");

    for (std::string line; std::getline(ifs, line); lineNo++)
    {
        if (std::regex_match(line, polygonExpression)) {
            std::string nextLine;
            std::getline(ifs, nextLine);
            lineNo++;

            auto startIndex = nextLine.find("fme");
            auto endIndex = nextLine.find_first_of("_", startIndex);
            if (startIndex != std::string::npos && endIndex != std::string::npos) {
                std::string id = nextLine.substr(startIndex, endIndex - startIndex);
                line.replace(line.size() - 1, 1, " gml:id=\"" + id + "\">");
            }

            ofs << line << std::endl;
            ofs << nextLine << std::endl;
        } else if (std::regex_match(line, bridgeConstructionElementExpression)) {
            auto startIndex = line.find("brid:BridgeConstructionElement");
            line.replace(startIndex, 30, "bldg:BuildingInstallation");
            ofs << line << std::endl;
        } else if (std::regex_match(line, outerBridgeConstructionExpression)) {
            auto startIndex = line.find("brid:outerBridgeConstruction");
            line.replace(startIndex, 28, "bldg:outerBuildingInstallation");
            ofs << line << std::endl;
        } else if (std::regex_match(line, outerBrideInstallationExpression)) {
            auto startIndex = line.find("brid:outerBridgeInstallation");
            line.replace(startIndex, 28, "bldg:outerBuildingInstallation");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeExpression)) {
            auto startIndex = line.find("brid:Bridge");
            line.replace(startIndex, 11, "bldg:Building");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeLod2GeometryExpression)) {
            auto startIndex = line.find("brid:lod2Geometry");
            line.replace(startIndex, 17, "bldg:lod2Geometry");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeGroundSurfaceExpression)) {
            auto startIndex = line.find("brid:GroundSurface");
            line.replace(startIndex, 18, "bldg:GroundSurface");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeOuterCeilingSurfaceExpression)) {
            auto startIndex = line.find("brid:OuterCeilingSurface");
            line.replace(startIndex, 24, "bldg:OuterCeilingSurface");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeWallSurfaceExpression)) {
            auto startIndex = line.find("brid:WallSurface");
            line.replace(startIndex, 16, "bldg:WallSurface");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeLod2MultiSurfaceExpression)) {
            auto startIndex = line.find("brid:lod2MultiSurface");
            line.replace(startIndex, 21, "bldg:lod2MultiSurface");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeOuterFloorSurfaceExpression)) {
            auto startIndex = line.find("brid:OuterFloorSurface");
            line.replace(startIndex, 22, "bldg:OuterFloorSurface");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeBoundedByExpression)) {
            auto startIndex = line.find("brid:boundedBy");
            line.replace(startIndex, 14, "bldg:boundedBy");
            ofs << line << std::endl;
        } else if (std::regex_match(line, bridgeLod2SolidOpenExpression)) {
            std::string nextLine;
            std::getline(ifs, nextLine);
            lineNo++;
            if (std::regex_match(line, bridgeLod2SolidCloseExpression) || std::regex_match(nextLine, bridgeLod2SolidCloseExpression)) {
                // skip
            } else {
                ofs << line << std::endl;
                ofs << nextLine << std::endl;
            }
        } else {
            ofs << line << std::endl;
        }
    }

    ifs.close();
    ofs.close();
    return 0;
}
