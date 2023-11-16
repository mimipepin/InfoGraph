#include "./../include/IndexedCubeRenderable.hpp"
#include "./../include/gl_helper.hpp"
#include "./../include/log.hpp"
#include "./../include/Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>


IndexedCubeRenderable::IndexedCubeRenderable(ShaderProgramPtr shaderProgram)
  : Renderable(shaderProgram), m_vBuffer(0)
{
	// Build the geometry : just a simple triangle for now
	m_positions.push_back( glm::vec3 (1,1,1) );
	m_positions.push_back( glm::vec3 (-1,1,1) );
	m_positions.push_back( glm::vec3 (-1,1,-1) );
	m_positions.push_back( glm::vec3 (1,1,-1) );
	m_positions.push_back( glm::vec3 (1,-1,1) );
	m_positions.push_back( glm::vec3 (-1,-1,1) );
	m_positions.push_back( glm::vec3 (-1,-1,-1) );
	m_positions.push_back( glm::vec3 (1,-1,-1) );

	m_colors.push_back(glm::vec4(0.4, 0.8, 0.8, 1.0)); //(r,g,b,a)
	m_colors.push_back(glm::vec4(0.2, 0.6, 0.2, 1.0));
	m_colors.push_back(glm::vec4(0.6, 0.8, 0.4, 1.0));
	m_colors.push_back(glm::vec4(0.7, 0.5, 0.4, 1.0));
	m_colors.push_back(glm::vec4(0.4, 0.5, 0.9, 1.0));
	m_colors.push_back(glm::vec4(0.6, 0.1, 0.3, 1.0));
	m_colors.push_back(glm::vec4(0.2, 0.1, 0.2, 1.0));
	m_colors.push_back(glm::vec4(0.1, 0.6, 0.7, 1.0));


	m_index = {0,1,3,
			1,2,3,
			1,5,2,
			5,6,2,
			1,5,4,
			1,4,0,
			4,0,3,
			4,3,7,
			5,6,7,
			4,5,7,
			6,2,7,
			2,7,3
	};


	// Set the model matrix to identity
	// m_model = glm::mat4(1.0);

	m_model = glm::translate(glm::mat4(), glm::vec3(-2,0,0));
	m_model = glm::rotate(m_model, -90.0f, glm::vec3(0,1,0));

	//Create buffers
	glGenBuffers(1, &m_vBuffer); //vertices

	//Activate buffer and send data to the graphics card
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_cBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
	// allocation de la mémoire du buffer et transfert de données du CPU au GPU.
	glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW); 

	glGenBuffers(1, &m_iBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size()*sizeof(int), m_index.data(), GL_STATIC_DRAW);

}

void IndexedCubeRenderable::do_draw()
{
	// Get the identifier ( location ) of the uniform modelMat in the shader program
	int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
	// Send the data corresponding to this identifier on the GPU
	glUniformMatrix4fv( modelLocation , 1, GL_FALSE , glm::value_ptr( m_model ));

	// Get the identifier of the attribute vPosition in the shader program
	int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
	// Activate the attribute array at this location
	glEnableVertexAttribArray( positionLocation );
	// Bind the position buffer on the GL_ARRAY_BUFFER target
	glBindBuffer( GL_ARRAY_BUFFER , m_vBuffer );
	// Specify the location and the format of the vertex position attribute
	glVertexAttribPointer( positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Colors 
	int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
	glEnableVertexAttribArray( colorLocation );
	glBindBuffer( GL_ARRAY_BUFFER , m_cBuffer ); // activation du buffer
	glVertexAttribPointer( colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Indexes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);

	// Draw the triangles
	// glDrawArrays( GL_TRIANGLES, 0, m_positions.size());
	glDrawElements(GL_TRIANGLES, m_index.size(), GL_UNSIGNED_INT, (void*)0);

	// Release the vertex attribute array
	glDisableVertexAttribArray( positionLocation );
	glDisableVertexAttribArray( colorLocation );
}

IndexedCubeRenderable::~IndexedCubeRenderable()
{
    glcheck(glDeleteBuffers(1, &m_vBuffer));
	glcheck(glDeleteBuffers(1, &m_cBuffer));
	glcheck(glDeleteBuffers(1, &m_iBuffer));
}
