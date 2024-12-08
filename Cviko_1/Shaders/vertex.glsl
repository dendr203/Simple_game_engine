#version 400

//uniforms that do not change with each vertex
uniform mat4 modelMatrix;							//modelov� matice, kter� ud�v�, jak se budou fragmenty chovat v glob�ln�m sou�adn�m syst�mu
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

   //t�m, �e jsou norm�ly ortogon�ln�, mus�me zajistit, �e m�n�me pouze jejich orientaci (sm�r), nikoliv d�lku nebo sklon
   //inverzn� matici m�me proto, �e pot�ebujeme vr�tit bod zp�t na jeho p�vodn� m�sto, abychom zpracovali norm�ly
   //transpozice je pot�eba, aby se i norm�ly spr�vn� transformovaly (vym�n� se ��dky se sloupci)
   mat4 normal = transpose(inverse(modelMatrix));									
   worldNormal = normalize(vec3(normal * vec4(in_Normal, 0.0)));

   //position of the vertex in world coordinates
   //pozice vrcholu se transformuje z modelov�ch sou�adnic do 2D obrazov�ch sou�adnic
   gl_Position = projectionMatrix * viewMatrix * fragPosition;

   //direction from the vertex to the camera
   //pozice kamery je v�dy na pozici [3] v matici viewMatrix
   //ode�teme pozici fragmentu ve sv�tov�ch sou�adnic�ch a z�sk�me vektor sm�ru od fragmentu ke kame�e
   viewDirection = normalize(vec3(inverse(viewMatrix)[3]) - vec3(fragPosition));

   //texture coordinates of the vertex, we scale them if needed
   texCoord = in_TexCoord * textureScale;
};