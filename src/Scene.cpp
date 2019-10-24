#include <iostream>
#include <fstream>

#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include <string>
#include "PrimTriangle.h"

void CScene::ParseOBJ(const std::string &fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	// --- PUT YOUR CODE HERE ---
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

	std::ifstream tmpFile;
	tmpFile.open(fileName, std::ios::out | std::ios::app | std::ios::binary);
	if (!tmpFile)
	{
		std::cout << "Unable to open file";
		exit(1); // terminate with error
	}

	int countV = 0, countf = 0;
	int VectorLines, faceLines; //to count line range of v and f in the OBJ file

	std::vector<float> vertexIndices; //array of all v's
	std::vector<float> temp_vertices; //array of all f's
	float vertex;
	float vertexIndex; //temporary variables to store in arrays

	//until the end of file
	while (tmpFile)
	{
		std::string lines;

		std::vector<std::string> tokens;
		// Read a Line from File
		getline(tmpFile, lines);

		char *token; //Tokenize by delimiting with " "
		token = strtok((char *)lines.c_str(), " ");

		while (token != NULL)
		{
			if (token[0] != 'f' && token[0] != 'v')
			{
				vertex = std::stof(token, nullptr); //convert string to float
				//std::cout << vertex << " ";
				temp_vertices.push_back(vertex); //add all values of v in temp_vertices
				countV++;
			}
			else if (token[0] == 'f')
			{
				break;
			}
			token = strtok(NULL, " ");
		}
		VectorLines = countV / 3; //1 to VectorLines in OBJ File has v
		while (token != NULL)
		{
			if (token[0] != 'f' && token[0] != 'v')
			{
				//std::cout << token << " ";
				vertexIndex = std::stof(token);
				vertexIndices.push_back(vertexIndex);
				countf++;
			}

			token = strtok(NULL, " ");
		}
	}
	faceLines = countf / 3;					  //f => VectorLines+1 to totalLines
	int totalLines = faceLines + VectorLines; //total number of lines in OBJ File

	tmpFile.close(); //close file

	for (int i = 0; i < (faceLines * 3); i += 3)
	{

		int pos_a1 = (vertexIndices[i] - 1) * 3;
		float A1 = temp_vertices[pos_a1] * 99.99f;
		float A2 = temp_vertices[pos_a1 + 1] * 99.99f;
		float A3 = temp_vertices[pos_a1 + 2] * 99.99f;

		int pos_b1 = (vertexIndices[i + 1] - 1) * 3;
		float B1 = temp_vertices[pos_b1] * 99.99f;
		float B2 = temp_vertices[pos_b1 + 1] * 99.99f;
		float B3 = temp_vertices[pos_b1 + 2] * 99.99f;

		int pos_c1 = (vertexIndices[i + 2] - 1) * 3;
		float C1 = temp_vertices[pos_c1] * 99.99f;
		float C2 = temp_vertices[pos_c1 + 1] * 99.99f;
		float C3 = temp_vertices[pos_c1 + 2] * 99.99f;

		this->Add(std::make_shared<CPrimTriangle>(Vec3f(A1, A2, A3), Vec3f(B1, B2, B3), Vec3f(C1, C2, C3), pShader));
	}

	std::cout << "Finished Parsing" << std::endl;
}
