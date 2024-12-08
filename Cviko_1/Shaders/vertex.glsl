#version 400

//uniforms that do not change with each vertex
uniform mat4 modelMatrix;							//modelová matice, která udává, jak se budou fragmenty chovat v globálním souøadném systému
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float textureScale;

//input atributes of each vertex
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;	

//output variables to fragment shader
out vec3 worldNormal;			//normal in world coordinates
out vec4 fragPosition;			//position of the vertex in world coordinates
out vec3 viewDirection;			//direction from the vertex to the camera
out vec2 texCoord;				//texture coordinates of the vertex


void main(void) 
{
   fragPosition = modelMatrix * vec4(in_Position, 1.0f);								//we need to change the position to world coordinates

   //tím, že jsou normály ortogonální, musíme zajistit, že mìníme pouze jejich orientaci (smìr), nikoliv délku nebo sklon
   //inverzní matici máme proto, že potøebujeme vrátit bod zpìt na jeho pùvodní místo, abychom zpracovali normály
   //transpozice je potøeba, aby se i normály správnì transformovaly (vymìní se øádky se sloupci)
   mat4 normal = transpose(inverse(modelMatrix));									
   worldNormal = normalize(vec3(normal * vec4(in_Normal, 0.0)));

   //position of the vertex in world coordinates
   //pozice vrcholu se transformuje z modelových souøadnic do 2D obrazových souøadnic
   gl_Position = projectionMatrix * viewMatrix * fragPosition;

   //direction from the vertex to the camera
   //pozice kamery je vždy na pozici [3] v matici viewMatrix
   //odeèteme pozici fragmentu ve svìtových souøadnicích a získáme vektor smìru od fragmentu ke kameøe
   viewDirection = normalize(vec3(inverse(viewMatrix)[3]) - vec3(fragPosition));

   //texture coordinates of the vertex, we scale them if needed
   texCoord = in_TexCoord * textureScale;
};