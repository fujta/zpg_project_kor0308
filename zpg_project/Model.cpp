#include "Model.h"

Model::Model(float* points, int pointCount) : points(points), pointCount(pointCount) {
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, pointCount * sizeof(float), points, GL_STATIC_DRAW);

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
        glDrawArrays(GL_TRIANGLES, 0, 92814);
    }
    else if (shapeType == SQUARE) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, pointCount / 3);
    }
    else {
		std::cout << "Warning! Missing shape type\n";
    }
}
