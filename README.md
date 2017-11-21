# rdPhysicalS

Este projeto é uma framework de renderização de cenas 3D, baseada na técnica de Ray Tracing, 
processadas em dispositivos de aceleração de hardware utilizando a OpenCL para programação paralela.

# Uso

Para utilização é necessário que o usuário tenha conhecimentos de c++.

Para a utilização da framework é bem simples. Basta o usuário criar uma cena e fazer
com que esta cena herde um cena base existente internemento na framework.

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

* Init: Local para ser inicializado todos os objetos interno;
* Update: Local onde será atualizado todos os dados necessários.

A classe SceneBase possui um camera interne pré-configurada, mas, o usuário possui a possibilidade 
de modificar essa configuralções pegando o retorno da instnacia da camera e utilizando a função
Configure.

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

SceneBase também possui uma função para adicionar objetos na cena, uma função para cada tipo de objetos
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
	

Função para criar a iluminção por ponto:

```c++
	CreatePointLight(RT::Vec3f(162.0f, 756.0f, 732.0f), WHITE, 1.0f);
```

Os parametros dessa função:
	
* position: ponto da luz;
* color: cor luz;
* ls: porcentagem do efeito da luz nos objetos;
* shadow: se vai haver calculo de sombra.


