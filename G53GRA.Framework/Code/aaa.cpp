#include "ObjectFileReader.h"

ObjectFileReader::ObjectFileReader(const char* fileName)
{
    m_fileName = fileName;
}

void ObjectFileReader::Read()
{
    std::ifstream fileStream(m_fileName, std::ios::in);
    std::string line;
    while (std::getline(fileStream, line))
    {
        if (firstWord(line) == "v")
        {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
    }else if (firstWord(line) == "usemtl")
    {
        std::istringstream s(line.substr(7));
        std::string mtlName;
        s >> mtlName;
        m_materials.push_back(mtlName);
    }
    }
}
ParseTexture(std::string textureName)
{
    std::string fileName = "Textures/" + textureName;
    std::ifstream fileStream(fileName, std::ios::in);
    std::string line;
    while (std::getline(fileStream, line))
    {
        if (firstWord(line) == "Ka")
        {
            std::istringstream s(line.substr(3));
            glm::vec3 Ka;
            s >> Ka.x >> Ka.y >> Ka.z;
        }
        else if (firstWord(line) == "Kd")
        {
            std::istringstream s(line.substr(3));
            glm::vec3 Kd;
            s >> Kd.x >> Kd.y >> Kd.z;
        }
        else if (firstWord(line) == "Ks")
        {
            std::istringstream s(line.substr(3));
            glm::vec3 Ks;
            s >> Ks.x >> Ks.y >> Ks.z;
        }
        else if (firstWord(line) == "Ns")
        {
            std::istringstream s(line.substr(3));
            float Ns;
            s >> Ns;
        }
        else if (firstWord(line) == "map_Kd")
        {
            std::istringstream s(line.substr(7));
            std::string textureName;
            s >> textureName;
            return textureName;
        }
        
