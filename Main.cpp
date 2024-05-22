//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include"Model.h"


const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL", then if fullscreen, then idk?
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);





	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-1.0f, -4.0f, 15.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	//Camera camera(width, height, glm::vec3(0.0f, 0.0f, 100.0f));
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 100.0f));


	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();

	std::string modelPath = "/Resources/test/Gear1.gltf";
	
	// Load in a model
	Model model0((parentDir + modelPath).c_str());
	Model model((parentDir + modelPath).c_str());
	Model model2((parentDir + modelPath).c_str());
	Model model3((parentDir + modelPath).c_str());
	Model model4((parentDir + modelPath).c_str());
	Model model5((parentDir + modelPath).c_str());


	// krecenie sie
	float oo = 0.0f;
	float rotationAngle = 0.0f;
	
	// kolorki zmiana
	float autt_i = 0.0f;
	float autt_j = 300.0f;
	float autt_k = 600.0f;
	float maxi = 1500.0f;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		float col1 = 1.0f / (maxi / autt_i);
		float col2 = 1.0f / (maxi / autt_j);
		float col3 = 1.0f / (maxi / autt_k);
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClearColor(col1, col2, col3, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(0.0f, 0.1f, 500.0f);


		// Draw models

		glm::quat leftRotation = glm::quat(cos(rotationAngle / 2.0f), sin(rotationAngle / 2.0f) * glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat rightRotation = glm::quat(cos(-rotationAngle / 2.0f), sin(-rotationAngle / 2.0f) * glm::vec3(0.0f, 1.0f, 0.0f));

		model0.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -11.65f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.2f, 20.0f, 0.2f)
		);

		model.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			leftRotation,
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		model2.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -23.3f),
			leftRotation,
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		model4.Draw(
			shaderProgram, camera, glm::mat4(1.0f), 
			glm::vec3(11.65f, 0.0f, -11.65f), 
			leftRotation,
			glm::vec3(1.0f, 2.0f, 1.0f)
		);
		model3.Draw(
			shaderProgram, camera, glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -11.65f),
			rightRotation,
			glm::vec3(1.0f, 4.5f, 1.0f)
		);
		model5.Draw(
			shaderProgram, camera, glm::mat4(1.0f), 
			glm::vec3(-11.65f, 0.0f, -11.65f), 
			leftRotation, 
			glm::vec3(1.0f, 2.0f, 1.0f)
		);
		
		// funny:
		//model5.Draw(shaderProgram, camera, glm::mat4(1.0f), glm::vec3(-11.65f, 0.0f, -30.0f), glm::quat((oo - 100.0f) / 100.0f, (oo - 100.0f) / 100.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.5f, 1.0f));

		//glm::mat4 matrix = glm::mat4(1.0f),
		//glm::vec3 translation = glm::vec3(15.0f, 15.0f, 0.0f),
		//glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		//glm::vec3 scale = glm::vec3(1.0f, 5.0f, 1.0f)

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

		// krecenie sie
		rotationAngle += 0.001f;
		//if (rotationAngle > 2.0f) { rotationAngle = 0.0f; }

		oo = oo + 1.0f;
		if (oo > 200.0f) { oo = 0.0f; }

		// zmiana kolorkow t³a
		autt_i = autt_i + 1.0f;
		if (autt_i > 900.0f) { autt_i = 0.0; }
		autt_j = autt_j + 1.0f;
		if (autt_j > 900.0f) { autt_j = 0.0; }
		autt_k = autt_k + 1.0f;
		if (autt_k > 900.0f) { autt_k = 0.0; }
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}