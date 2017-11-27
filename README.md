# rdPhysicalS

Este projeto é uma framework de renderização de cenas 3D, baseada na técnica de Ray Tracing. E o 
processamento dos dados ocorre em dispositivos de aceleração de hardware, utilizando a OpenCL para programação paralela. 

# Uso

Para utilização, é necessário que o usuário tenha conhecimentos de c++. E, possua dispositivos compativeis com a OpenCL,
exemplo dispositivos da Intel, AMD, Nvidia.

Para facilitar, a framework possui um componente interno de calculos matemáticos de vetores e matrizes, com os componentes:

* Vetor 2 - RT::Vec2f;
* Vetor 3 - RT::Vec3f;
* Vetor 4 - RT::Vec4f;
* Matriz 3x3 - RT::Mat3f;
* Matriz 4x4 - RT::Mat4f;

para utiliza-los basta inclui-los em seu código com:

```c++
	#include <RTmath.h>
```

Para a utilização da framework, antes de tudo deve-se inicializar os componenetes internos da aplicação, com a função:

```c++
	rdps::World::Init();
```

Essa função verifica-rá se existe algum dispositivo compativel com OpenCL, o inicializa-rá e criará os pacotes necessários
para a geração da cena.

Depois de inicializar, deve-se setar o tamanho da janela com os parameros desejados, através da função:

```c++
	rdps::World::SetViewPlane(1920, 1080);
```

Logo após deve-se definir a qualidade da imagem com a função:

```c++
	rdps::World::Quality(VERY_LOW);
```

existem 5 opções:

* VERY_LOW == 1
* LOW == 4
* MEDIUM == 16
* HIGH == 64
* VERY_HIGH == 144

A qualidade é equivalente ao número de raios laçados por pixel, quanto maior o número melhor a qualidade.

Obs: quanto maior a qualidade mais processamento, mais demorado vai ser.

# Importante

O sistema de coordenadas é em numeros inteiros, com o 0x0 no centro da tela. Então se a janela for 800x600, em x irá de 
-400 a 400, com a esquerda sedo negativo e a direita positivo, y irá de 300 a -300 com a parte superior positivo e inferior negativo. E,
z negativo para o lado do observador e positivo apontando para a cena.

Depois, Deve-se criar uma cena e herdar da classe SceneBase.

Exemplo:

```c++
	#include "..\rdps-frwk\base\SceneBase.h"
	
	class TestScene : public rdps::frwk::SceneBase
	{
	public:
		TestScene();
		~TestScene();
		
		virtual void Init();
		virtual void Update(const float secs);
	}
```
	
As funções Init() e Update(const float secs) é obrigatório ser sobreescrito.

* Init: Local para ser inicializado todos os objetos internos;
* Update: Local onde será atualizado todos os dados necessários.

A classe SceneBase possui uma camera interne pré-configurada, mas, o usuário tem a possibilidade 
de modificar as configurações, pegando o retorno da instancia da camera e utilizando a função
Configure para modifica-lá.

Exemplo:

```c++
	GetCamera()->Configure(RT::Vec3f(-702.0f, -108.0f, -270.0f), 
						   RT::Vec3f(-540.0f, -100.0f, 0.0f), 
						   RT::Vec3f(0.0f, 1.0f, 0.0f), 
						   800.0f, 1.5f);
```
						   
Os parametros dessa função:

* eye: ponto de visão (posição inicial da camera);

* lookAt: para onde a camera está olhado;

* up: onde é a parte de cima da camera;

* viewPlaneDistance: a distancia do plano de foco;

* zoom: zoom da camera.

Possui uma luz ambiente também pré-configurada, com a possibilidade de fazer alterações.
Basta pegar o retorno da instancia.

Exemplo:

```c++
	GetAmbientLight()->SetColor(0.8f, 0.8f, 0.8f);
	GetAmbientLight()->SetLs(1.0f);
```

* AmbientLight: é um componete de luaz básica para simular a luz ambiente da cena. Ela possui um vetor
 (RT::Vec3f color;) referente a cor e um ponto flutuante (float ls;) que é o percentual da iluminação
 da luz ambiente.

SceneBase também possui uma função para adicionar objetos na cena, uma para cada tipo de objetos
e também uma função para adicionar a iluiminação, uma para cada tipo. Todas essas funções retornam um
id (int) referente a posição do objeto na lista.

Função para criar um plano:

```c++
	CreatePlane(RT::Vec3f(0.0f, -324.0f, 0.0f), 
				RT::Vec3f(0.0f, 1.0f, 0.0f), 
				new PhongMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f), 
								  0.2f, 0.7f, 0.5f, 1.0f));
		
```	
	
Os parametros dessa função:
	
* point: posição do plano;
* normal: normal do plano (obs: a normal do plano define o para onde está apontado a face);
* material: material do plano.

Tipo de retorno int, que é o id do objeto na lista de objetos.
	
Função para criar a esfera:

```c++
	CreateSphere(RT::Vec3f(-540.0f, -86.0f, 432.0f), 270.0f,
				 new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
								   0.2f, 0.7f, 0.8f, 1.0f));

```

Os parametros dessa função:
	
* center: posição da esfera;
* radius: raio da esfera (define o tamanho da esfera);
* material: material ds esfera;
	
Tipo de retorno int, que é o id do objeto na lista de objetos.

Função para criar um cubo:

```c++
	CreateCube(RT::Vec3f(0.0f, -324.0f, 270.0f), 
			   RT::Vec3f(324.0f, 162.0f, 324.0f),
			   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
								 0.2f, 0.7f, 0.2f, 1.0f));
```

Os parametros dessa função:
	
* initPoint: ponto inicial do cubo (obs: iniciar o cubo da esquerda para a direita e em direção a o fundo);
* size: ponto final do cubo;
* material: material do cubo.

Tipo de retorno int, que é o id do objeto na lista de objetos.	

Função para criar a iluminção por ponto:

```c++
	CreatePointLight(RT::Vec3f(162.0f, 756.0f, 732.0f), WHITE, 1.0f);
```

Os parametros dessa função:
	
* position: ponto da luz;
* color: cor luz;
* ls: porcentagem do efeito da luz nos objetos;
* shadow: se haverá calculo de sombra.

Tipo de retorno int, que é o id da iluminação na lista de luzes.

# Referente ao Material

Os materiais por padrão herdão de um material base. Esse material base possui um componente BRDF que é referente 
o efeito (cor) do componente Ambient do material. Então todos os materiais possuirão uma cor ambiente.

* BRDF: é um component do material que simplesmente possui um vector (RT::Vec3f color;) referente a
  cor, um ponto flutuante (float k;) que é o percentual que a cor afetará o objeto, e um tipo (TypeBRDF type;)
  para diferenciar no calculo de cor do material, que pode ser: Ambient, Diffuse, Specular, Reflective.
 
  Possui 3 construtores:

  -> um construtor de cópia;
  -> um construtor só para definir o tipo do componente (utilizado para herança);
  -> e o construtor oficial, para setar os dados nos atributos.

Exemplo:

```c++ 
	BRDF(RT::Vec3f(0.6f, 0.5f, 0.2f), 0.2f); 
```

* GlossySpecular: também é uma componente BRDF do material, só que mais expecífico. É o componente Specular do material Phong. 
  Essa classe herda os atributos da classe BRDF, com um ponto flutuante a mais (float exp;) para o calculo do efeito specular.

  Possui 2 construtores:

  -> um construtor de cópia;
  -> e o construtor oficial para setar os dados nos atributos.

Exemplo:

```c++ 
  	GlossySpecular(RT::Vec3f(0.7f, 0.6f, 0.6f), 0.8f, 1.0f); 
```

# Simple material

Possui apenas 2 Componetes BRDF de cor Ambient e Diffuse. 

Possui 2 Construtores;

* 1*
```c++ 
	SimpleMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.2f, 0.7f);
```

	Esse construtor recebe como parametro um vetor (RT::Vec3f color) que é a cor padrão para todos os componetes BRDF, um percentual para 
	a cor Ambient (float ambient;) e um percentual para a cor diffusa (float diffuse;);

* 2* 
```c++ 
	SimpleMaterial(new BRDF(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.2f), new BRDF(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.7f));
```

	Esse construtor recebe como parametro 2 componentes BRDF, ambient e diffuse. Pois cada componente pode possuir a cor diferentes do outro.

# PhongMaterial

Possui 3 Componetes BRDF (cor) Ambient, Diffuse e Specular (GlossySpecular).

Possui 2 Construtores;

* 1* 
```c++ 
	PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f), 0.2f, 0.7f, 0.8f, 1.0f);
```

	Esse construtor recebe como parametro um vetor (RT::Vec3f color;) que é a cor padrão para todos os componetes BRDF, um percentual 
	para a cor ambient (float ambient;), um percentual para a cor diffusa (float diffuse;), um percentual para a cor specular (float specular;) 
	e um expoente para a intensidade da specular (float intensit;);

* 2* 
```c++ 
	PhongMaterial(new BRDF(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.2f), new BRDF(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.7f));
```

	Esse construtor recebe como parametro 3 componentes BRDF, ambient, diffuse, Specular (GlossySpecular). Pois cada componente pode possuir a 
	cor diferente dos outros.

# Objetos

Para recuperar os objetos deve-se indicar o indice (id) desse objeto na lista.

Exemplo:

```c++ 
	int id;
	rdps::frwk::Sphere *s = dynamic_cast<rdps::frwk::Sphere>(GetObject(id));
```

O tipo de retorno dessa função (GetObject) é um GeometricObject e se não se sabe o tipo do objeto que está no id desejado, e necessita 
de uma esfera por exemplo, é necessário fazer a converção com dynamic_cast, pois, se não for uma esfera ele retorna-rá nulo. Mas, se no ato 
da criação foi quardado o id do objeto basta pegar a referência diretamente.

```c++ 
	rdps::frwk::Sphere *s = GetObject(id);
```

Os objetos possuem internamente um componente de transformações (Transform), com as transformações básicas translação, rotação, escala.
Para transformar basta recuperar a instancia do componete e utilizar a função desejada;

* Translate: possui 2 funções sobrecarregadas, uma recebe um vetor3 (RT::Vec3f position) como parametro e a outra recebe 3 pontos flutuantes
(float x, float y, float z) que é referente a posição final;

Exemplo:

```c++
	GetObject(id)->GetTransform()->Translate(RT::Vec3f(10.0f, -200.0f, 400.0f));
``` 

```c++
	GetObject(id)->GetTransform()->Rotate(10.0f, -200.0f, 400.0f);
```

* Rotate: para a rotação, possui 3 funções separas, uma para cada eixo. RotateX, RotateY, RotateZ e pra trabalhar com elas deve-se trabalhar em
  angulos, pois internmente é convertido em radiano.

Exemplo:

```c++
	GetObject(id)->GetTransform()->RotateX(90.0f);
``` 

```c++
	GetObject(id)->GetTransform()->RotateY(-225.0f);
```

```c++
	GetObject(id)->GetTransform()->RotateZ(45.0f);
```

* Escala: possui 3 funções sobrecarregadas, uma recebe um vetor3 (RT::Vec3f position) como parametro, outra recebe 3 pontos flutuantes
 (float x, float y, float z) e outra um ponto flutuante.

Exemplo:

```c++
	GetObject(id)->GetTransform()->Scale(RT::Vec3f(100.0f, 200.0f, 400.0f));
``` 

```c++
	GetObject(id)->GetTransform()->Scale(100.0f, 200.0f, 400.0f);
```

Nestes 2 casos acima pode-se scalar o objeto de formas diferente.


```c++
	GetObject(id)->GetTransform()->Scale(100.0f);
```

Neste acima a escala é totalmente iqual em todos os eixos.


# Exemplo cena

Test.h

```c++
#ifndef	__TEST_H__
#define	__TEST_H__

#include "..\rdps-frwk\base\SceneBase.h"

class Test : public frwk::SceneBase
{
private:
	int id;

public:
	Test();
	~Test();

	virtual void Init();
	virtual void Update(const float secs);
};


#endif//__TEST_H__
```


Test.cpp

```c++
#include "Test.h"
#include "..\rdps-frwk\includes_frwk.h"

using namespace rdps;

Test::Test() :
	frwk::SceneBase()
{
	Init();
}

Test::~Test()
{
}

void Test::Init()
{
	GetCamera()->Configure(RT::Vec3f(-702.0f, -108.0f, -270.0f), 
						   RT::Vec3f(-540.0f, -100.0f, 0.0f), 
						   RT::Vec3f(0.0f, 1.0f, 0.0f), 
						   800.0f, 1.5f);

	/*Adiciona as luzes*/
	CreatePointLight(RT::Vec3f(162.0f, 756.0f, 732.0f), WHITE, 1.0f);
	CreatePointLight(RT::Vec3f(-540.0f, 756.0f, 432.0f), WHITE, 1.0f);

	/*Adiciona os planos*/
	CreatePlane(RT::Vec3f(0.0f, -324.0f, 0.0f), 
				RT::Vec3f(0.0f, 1.0f, 0.0f), 
				new PhongMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f), 
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(0.0f, 0.0f, 2419.0f),
				RT::Vec3f(0.0f, 0.0f, -1.0f),
			    new PhongMaterial(RT::Vec3f(0.6f, 0.5f, 0.5f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(-1296.0f, 0.0f, 0.0f),
				RT::Vec3f(1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.6f, 0.6f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(1296.0f, 0.0f, 0.0f),
				RT::Vec3f(-1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.6f, 0.6f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(0.0f, 800.0f, 0.0f),
				RT::Vec3f(0.0f, -1.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	/*Adiciona as esferas*/
	CreateSphere(RT::Vec3f(162.0f, 54.0f, 432.0f), 216.0f,
				 new PhongMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
								   0.2f, 0.7f, 0.8f, 1.0f));

	id = CreateSphere(RT::Vec3f(-540.0f, -86.0f, 432.0f), 270.0f,
					  new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
										0.2f, 0.7f, 0.8f, 1.0f));

	/*Adiciona o Cubo*/
	CreateCube(RT::Vec3f(0.0f, -324.0f, 270.0f), 
			   RT::Vec3f(324.0f, 162.0f, 324.0f),
			   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
								 0.2f, 0.7f, 0.2f, 1.0f));
}

void Test::Update(const float secs)
{
	GetObject(id)->GetTransform()->Translate(10.0f, -200.0f, 400.0f);
}
```


