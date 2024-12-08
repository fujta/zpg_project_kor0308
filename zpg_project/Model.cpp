#include "Model.h"

Model::Model() {}

Model::Model(float* points, GLsizeiptr pointCount) : points(points), pointCount(pointCount) {
	this->VAO = 0;
	this->VBO = 0;
     
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, pointCount, points, GL_STATIC_DRAW);
	// if error violation occurs, check the size of the buffer

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::render(ShapeType shapeType) {
    glBindVertexArray(VAO);

    if (shapeType == TRIANGLE || shapeType == BUSH) {
		glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount / 3);
    }
    else if (shapeType == TREE) {
        glDrawArrays(GL_TRIANGLES, 0, pointCount);
    }
    else if (shapeType == SQUARE) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, pointCount / 3);
	}
	else if (shapeType == SPHERE) {
		glDrawArrays(GL_TRIANGLES, 0, pointCount / 3);
	}
    else if (shapeType == PLAIN) {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else if (shapeType == SKYCUBE) {
        glDrawArrays(GL_TRIANGLES, 0, 108);
	}
    else {
		std::cout << "Warning! Missing shape type in model.cpp\n";
		throw std::runtime_error("Missing shape type in model.cpp");
    }
}
