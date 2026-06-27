# Proyecto Semestral - Estructuras de Datos


## Integrantes

* Camila García Torres - agregar matrícula D:
* Javiera Paris Osses - 2023453170
* Diego Matus Salas - 2023900249


## Datasets Seleccionados


| Dataset | Tipo de Red | Vértices (Nodos) | Aristas (Enlaces) | Fuente |
| :--- | :--- | :--- | :--- | :--- |
| **Yeast Protein Network** | No dirigida, sin peso | Proteínas | Interacciones biológicas | [Kaggle - Yeast Dataset](https://www.kaggle.com/datasets/alexandervc/yeast-proteinprotein-interaction-network) |
| **IMDb Actors Network** | No dirigida, con peso | Actores | Co-aparición en películas | [Kaggle - IMDb Dataset](https://www.kaggle.com/datasets/aditijuneja/imdb-actors-network-dataset) |


## Métricas Implementadas

El proyecto analiza la topología de los grafos mediante 7 métricas clave:

1.  **Degree Centrality (Grado):** Conectividad directa de los nodos.
2.  **Betweenness Centrality (Intermediación):** Control del flujo de información (Algoritmo de Brandes).
3.  **Closeness Centrality (Cercanía):** Capacidad de comunicación rápida en la red.
4.  **PageRank:** Importancia estructural mediante recorridos aleatorios.
5.  **Average Shortest Path:** Distancia promedio global del grafo.
6.  **Subgraph Centrality:** Participación en circuitos cerrados.
7.  **Clustering Coefficient:** Tendencia de la red a agruparse localmente (triángulos).



---

Debido al gran tamaño de los datasets, **estos no se suben al repositorio**. Se tienen que agregar a la carpeta `/data`.

Para compilar, se debe ejecutar
```bash
g++ -O3 main.cpp grafos.cpp algoritmosUtil.cpp calc*.cpp -o main
```