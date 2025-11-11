#ifndef SHADER_H
#define SHADER_H

#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	// the program ID
	unsigned int ID;

public:
	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functins
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setMat2(const std::string& name, const glm::mat2& mat);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);
};

#endif
