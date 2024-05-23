//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include"Model.h"

#define M_PI 3.14159265358979323846

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// initialize GLFW
	glfwInit();

	// tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL", then if fullscreen, then idk?
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

	// error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// introduce the window into the current context
	glfwMakeContextCurrent(window);

	// load GLAD so it configures OpenGL
	gladLoadGL();

	// specify the viewport of OpenGL in the Window
	glViewport(0, 0, width, height);

	// generate Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// adjust the light
	glm::vec3 dirLightDirection = glm::vec3(0.0f, 1.0f, 0.0f); // adjust to the desired direction
	glm::vec4 dirLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // white light

	// send light information to the shader
	shaderProgram.Activate();
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "dirLightDirection"), dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "dirLightColor"), dirLightColor.x, dirLightColor.y, dirLightColor.z, dirLightColor.w);

	// enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// create camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 100.0f));

	// paths to resources (models, textures)
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/test/Gear1.gltf";
	std::string modelUPath = "/resources-chair/gltf/barstool.gltf";
	
	// load in a model
	Model modelU1((parentDir + modelUPath).c_str()); // chair
	Model model((parentDir + modelPath).c_str()); // gear
	Model model2((parentDir + modelPath).c_str()); // gear
	Model model3((parentDir + modelPath).c_str()); // gear
	Model model4((parentDir + modelPath).c_str()); // gear
	Model model5((parentDir + modelPath).c_str()); // gear

	// rotation variable
	float rotationAngle = 0.0f;
	
	// variables to help change background's colors
	float autt_i = 0.0f;
	float autt_j = 300.0f;
	float autt_k = 600.0f;
	float maxi = 1500.0f;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// calculate background's colors
		float col1 = 0.5f * sin(autt_i * 2.0f * M_PI / maxi) + 0.5f;
		float col2 = 0.5f * sin(autt_j * 2.0f * M_PI / maxi) + 0.5f;
		float col3 = 0.5f * sin(autt_k * 2.0f * M_PI / maxi) + 0.5f;

		glClearColor(col1, col2, col3, 1.0f);

		// clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// handle camera inputs
		camera.Inputs(window);

		// update and export the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 500.0f);

		// calculate rotation
		glm::quat leftRotation = glm::quat(cos(rotationAngle / 2.0f), sin(rotationAngle / 2.0f) * glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat rightRotation = glm::quat(cos(-rotationAngle / 2.0f), sin(-rotationAngle / 2.0f) * glm::vec3(0.0f, 1.0f, 0.0f));

		// draw models
		/*modelU1.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, -39.0f, -11.65f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.3f, 1.3f, 1.3f)
		);*/
		model.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			leftRotation,
			glm::vec3(1.0f, 1.5f, 1.0f)
		);
		model2.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -23.3f),
			leftRotation,
			glm::vec3(1.0f, 1.5f, 1.0f)
		);
		model4.Draw(
			shaderProgram, camera, glm::mat4(1.0f), 
			glm::vec3(11.65f, 0.0f, -11.65f), 
			leftRotation,
			glm::vec3(1.0f, 1.5f, 1.0f)
		);
		model3.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -11.65f),
			rightRotation,
			glm::vec3(1.0f, 1.5f, 1.0f)
		);
		model5.Draw(
			shaderProgram, camera, glm::mat4(1.0f), 
			glm::vec3(-11.65f, 0.0f, -11.65f), 
			leftRotation, 
			glm::vec3(1.0f, 1.5f, 1.0f)
		);
		
		//glm::mat4 matrix = glm::mat4(1.0f),
		//glm::vec3 translation = glm::vec3(15.0f, 15.0f, 0.0f),
		//glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		//glm::vec3 scale = glm::vec3(1.0f, 5.0f, 1.0f)

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();

		// rotation
		rotationAngle += 0.001f;

		// updating background color
		autt_i += 1.0f;
		if (autt_i > maxi) autt_i = 0.0f;
		autt_j += 1.0f;
		if (autt_j > maxi) autt_j = 0.0f;
		autt_k += 1.0f;
		if (autt_k > maxi) autt_k = 0.0f;
	}

	// delete all the objects we've created
	shaderProgram.Delete();
	// delete window before ending the program
	glfwDestroyWindow(window);
	// terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}