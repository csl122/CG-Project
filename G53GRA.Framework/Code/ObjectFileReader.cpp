#include "ObjectFileReader.h"


ObjectFileReader::ObjectFileReader(string& filePath)
{
	_path = filePath;
}


ObjectFileReader::~ObjectFileReader()
{
}

void ObjectFileReader::Load() {
	ifstream fileStream(_path, ios_base::in);

	if (!fileStream) {
		cout << "Error opening '" << _path << "'" << endl;
		return;
	}

	bool noRender = false;
	int currentMaterial = -1;

	string line;
	while (getline(fileStream, line)) {
		if (line.length() == 0 || line[0] == '#') continue; // skip line if nothing there or if line is commented

		stringstream lineStream(line);
		string firstWord;
		lineStream >> firstWord;

		if (firstWord.length() == 0) continue; // skip if no first word found

		if (firstWord == "v") {
			// vertex
			vertices.push_back(ParseVector(lineStream));
		}
		else if (firstWord == "vt") {
			// vertex texture coordinate
			textureCoordinates.push_back(ParseTextureCoordinate(lineStream));
		}
		else if (firstWord == "vn") {
			// vertex normal
			normals.push_back(ParseVector(lineStream));
		}
		else if (firstWord == "f") {
			// face
			if (noRender) continue;
			faces.push_back(ParseObjectFace(lineStream));

		}
		else if (firstWord == "usemtl") {
			// material used: not fully implemented
			string materialName;
			lineStream >> materialName;
			if (materialName == "material_norender") {
				noRender = true;
				currentMaterial = -1;
			}
			else {
				noRender = false;
			}
		}

	}
	fileStream.close();
}

Vertex* ObjectFileReader::ParseVector(stringstream& ls) {
	float x, y, z;
	ls >> x >> y >> z;
	return new Vertex(x, y, z);
}

float* ObjectFileReader::ParseTextureCoordinate(stringstream& ls) {
	float x, y;
	ls >> x >> y;
	return new float[2]{ x, y };
}

Face* ObjectFileReader::ParseObjectFace(stringstream& ls) {
	// 3 or 4 vertex polygons (triangles/quads)
	Face* face = new Face();

	string encodedFace;

	while (ls >> encodedFace) {

		Vertex* data = new Vertex();
		data->x = -1; // vertex position
		data->y = -1; // texture position
		data->z = -1; // material position

		size_t firstPos = encodedFace.find('/');
		size_t secondPos = encodedFace.find('/', firstPos + 1);

		bool textureCoordinateExists = secondPos - firstPos > 1;
		bool normalCoordinateExists = encodedFace.length() - secondPos > 1;

		data->x = (float)stoi(encodedFace.substr(0, firstPos).c_str()) - 1; // index of the current vertex in the file

		if (textureCoordinateExists)
			data->y = (float)stoi(encodedFace.substr(firstPos + 1, secondPos - firstPos).c_str()) - 1; // index of the texture coordinate

		if (normalCoordinateExists)
			data->z = (float)stoi(encodedFace.substr(secondPos + 1, encodedFace.length() - secondPos).c_str()) - 1; // index of the material coordinate

		face->faceData->push_back(data);
	}

	return face;
}