#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>

class Shader
{
	GLuint shader;

	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);
	bool checkOpenGLError(void);
    std::string readShaderSource(const char *filePath);
    GLuint createShaderProgram(const char* vertShader, const char* fragShader);

    public:
        Shader() = default;
        Shader(const char* vertShader, const char* fragShader);
        void createProgram(const char* vertShader, const char* fragShader);
        void activateShader(void);
        void deleteShader(void);
};
