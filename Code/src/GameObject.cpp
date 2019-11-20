#include "GameWrap.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::shared_ptr<Texture> _texture, 
	std::shared_ptr<VertexArray> _vertexArray) : m_texture(_texture),
	m_vertexArray(_vertexArray) {}

GameObject::GameObject(std::shared_ptr<Texture> _texture, 
	std::shared_ptr<VertexArray> _vertexArray, 
	std::shared_ptr<ShaderProgram> _defaultShader) : m_texture(_texture),
	m_vertexArray(_vertexArray), m_defaultShader(_defaultShader) {}

GameObject::~GameObject()
{

}

void GameObject::update()
{

}

void GameObject::draw()
{
	if (m_defaultShader != nullptr)
	{
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, m_model.m_position);
		modelMat = glm::rotate(modelMat, glm::radians(m_model.m_rotation.y), glm::vec3(0, 1, 0));
		m_defaultShader->setUniform("in_Model", modelMat);
		m_defaultShader->setUniform("in_Texture", m_texture);
		m_defaultShader->draw(m_vertexArray);
	}
}

void GameObject::draw(std::shared_ptr<RenderTexture> _rt)
{
	if (m_defaultShader != nullptr)
	{
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, m_model.m_position);
		modelMat = glm::rotate(modelMat, glm::radians(m_model.m_rotation.y), glm::vec3(0, 1, 0));
		m_defaultShader->setUniform("in_Model", modelMat);
		m_defaultShader->setUniform("in_Texture", m_texture);
		m_defaultShader->draw(_rt, m_vertexArray);
	}
}

void GameObject::draw(std::shared_ptr<ShaderProgram> _shader)
{
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, m_model.m_position);
	modelMat = glm::rotate(modelMat, glm::radians(m_model.m_rotation.y), glm::vec3(0, 1, 0));
	_shader->setUniform("in_Model", modelMat);
	_shader->setUniform("in_Texture", m_texture);
	_shader->draw(m_vertexArray);
}

void GameObject::draw(std::shared_ptr<RenderTexture> _rt, std::shared_ptr<ShaderProgram> _shader)
{
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, m_model.m_position);
	modelMat = glm::rotate(modelMat, glm::radians(m_model.m_rotation.y), glm::vec3(0, 1, 0));
	_shader->setUniform("in_Model", modelMat);
	_shader->setUniform("in_Texture", m_texture);
	_shader->draw(_rt, m_vertexArray);
}

void GameObject::setModel(Model _model, int _id)
{
	if (_id < 0 || _id >= m_hitboxes.size())
	{
		return;
	}
	m_hitboxes.at(_id) = _model;
}

void GameObject::deleteModel(int _id)
{
	if (_id < 0 || _id >= m_hitboxes.size())
	{
		return;
	}
	m_hitboxes.erase(m_hitboxes.begin() + _id);
}

Model GameObject::getModel(int _id)
{
	if (_id < 0 || _id >= m_hitboxes.size())
	{
		Model empty;
		return empty;
	}
	return m_hitboxes.at(_id);
}
