#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include <SDL2/SDL.h>

class Texture;
class VertexArray;
class ShaderProgram;
class RenderTexture;
class DepthBuffer;

// Stores data for individual hitboxes of the model

struct Model
{
	// Name of GameObject piece (useful for animation)
	std::string m_bone;
	// Position in object space
	glm::vec3 m_position;
	// Orientation of model
	glm::vec3 m_rotation;
	// Scale of hitbox
	glm::vec3 m_scale;
};

// Stores data for objects in scene

class GameObject
{
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<ShaderProgram> m_defaultShader;

	// Stores world space values
	Model m_model;
	// Stores individual hitboxes for limbs
	std::vector<Model> m_hitboxes;
public:
	// Constructor
	GameObject();
	// Constructor overload1
	GameObject(std::shared_ptr<Texture> _texture, 
		std::shared_ptr<VertexArray> _vertexArray);
	// Constructor overload2
	GameObject(std::shared_ptr<Texture> _texture,
		std::shared_ptr<VertexArray> _vertexArray,
		std::shared_ptr<ShaderProgram> _defaultShader);

	~GameObject();

	// Update to be called in Game loop
	virtual void update();

	virtual void draw();
	virtual void draw(std::shared_ptr<RenderTexture> _rt);
	virtual void draw(std::shared_ptr<ShaderProgram> _shader);
	virtual void draw(std::shared_ptr<RenderTexture> _rt, 
		std::shared_ptr<ShaderProgram> _shader);
	virtual void draw(std::shared_ptr<DepthBuffer> _db,
		std::shared_ptr<ShaderProgram> _shader);

	// Getters and setters
	void setInitialModel(Model _model) { m_model = _model; }
	void setModel(Model _model, int _id);
	void addModel(Model _model) { m_hitboxes.push_back(_model); }
	void deleteModel(int _id);

	Model getInitialModel() { return m_model; }
	int getModelTotal() { return m_hitboxes.size(); }
	Model getModel(int _id);
};