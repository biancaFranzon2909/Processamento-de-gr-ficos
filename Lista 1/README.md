# Lista 1
---

## Descrição do Projeto

Este programa foi desenvolvido como parte da disciplina *Processamento Gráfico* com o objetivo de aplicar conceitos de OpenGL moderna e C++ na criação de imagens simples.

---

## Estrutura do Projeto

| Arquivo                  | Descrição                                                                 |
|--------------------------|---------------------------------------------------------------------------|
| `cmakeLists.txt`               | Arquivo de configuração do Cmake para funcionamento das atividades, a partir dele é possível rodar o comando build    |

|...|...|

---

## Informações Técnicas

- **Linguagem:** C++ (C++11 ou superior)  
- **API Gráfica:** OpenGL 3.3+ (core profile)  
- **Dependências:** GLFW, GLAD, stb_image, glm  
- **IDE/Compilador:** Visual Studio Code / MinGW / CMake 
- **Plataforma-alvo:** Windows

---

---

## Screenshots / Vídeo de Gameplay (**OPCIONAL!!**)

Inclua aqui imagens do programa em execução ou link para um vídeo.  

<img width="802" height="593" alt="image" src="https://github.com/user-attachments/assets/5351bd1b-9b12-43f9-ba32-eebff7e818cc" />
<img width="781" height="581" alt="image" src="https://github.com/user-attachments/assets/f6de0c76-5c24-40ba-8713-450f72f86acd" />
<img width="793" height="591" alt="image" src="https://github.com/user-attachments/assets/c41043e7-1626-4b1a-bfd6-400c7a1efa6f" />
<img width="801" height="581" alt="image" src="https://github.com/user-attachments/assets/a7e0a099-5e81-40a0-8be0-0410ec20d511" />
<img width="788" height="590" alt="image" src="https://github.com/user-attachments/assets/f890a8d5-c431-49f9-8230-9866260d18c5" />
<img width="781" height="577" alt="image" src="https://github.com/user-attachments/assets/7483f523-fefb-41bc-bd0e-df4b6a4bdae9" />
<img width="787" height="592" alt="image" src="https://github.com/user-attachments/assets/dadf34ea-68b8-4a38-9c05-c678887594d4" />
<img width="792" height="588" alt="image" src="https://github.com/user-attachments/assets/adbd4f07-e87c-4468-aa72-5228f50ce3f5" />
<img width="785" height="585" alt="image" src="https://github.com/user-attachments/assets/90f11f32-2787-4ea9-a6b7-9c613f721c35" />
<img width="778" height="567" alt="image" src="https://github.com/user-attachments/assets/c5969ec8-7355-4798-a448-8b9da4e20b18" />
<img width="792" height="583" alt="image" src="https://github.com/user-attachments/assets/8bbc8fe6-7711-4917-b790-c89c60fa8a35" />
<img width="785" height="581" alt="image" src="https://github.com/user-attachments/assets/d20c87dc-308f-49ee-8be4-f8bf8d76b8d8" />

---

## Respostas:
* a) Descreva uma possível configuração dos buffers (VBO, VAO) para representá-lo. 
* Para esse exercício foi adicionado no VBO as cores de cada um dos vértices intercalada com sua posição. Quanto ao VAO destacamos como atributo 0 a leitura das posições e no atributo 1 a leitura das cores.
* b) Como estes atributos seriam identificados no vertex shader?
* No vertex shader os atributos vindos do VAO são declarados na entrada com o "in" e mapeados como position e como color para que ao rodar, o triângulo faça display certo.
  
---

<img width="793" height="596" alt="image" src="https://github.com/user-attachments/assets/aa6a4f22-013e-419e-a29a-d97d8734db1f" />
Desenho selecionado: cachorro, feito por mim no paint :)
