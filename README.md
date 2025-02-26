<h1 align = "center">Medidor sonoro em placa BitDogLab com respostas visuais em outros componentes</h1>

<p align = "center">O projeto apresentado utiliza a placa BitDogLab e seus componentes juntamente com a linguagem C para desenvolver
  um medidor sonoro com respostas visuais em outros componentes</p>

---
<h3>🎯 Objetivos</h3>
<p>O programa desenvolvido em Linguagem C para placa Pi Pico W tem como principais objetivos:</p>

- ☑️ Capturar o som utilizando o microfone (conectado à GPIO 28, Channel: 2)
- ☑️ Apresentar um gráfico de som na matriz de LEDS 5x5 WS2812(conectada à GPIO 7)
- ☑️ Fazer o Botão A (conectado à GPIO 5) pause a execução do programa até que seja pressionado novamente
- ☑️ Fazer o Botão B (conectado à GPIO 6) pare a execução por 2 segundos, após esse tempo a execução continua
- ☑️ Fazer o Buzzer A (conectado à GPIO 21) emita um alerta ao passar do nível 100 de volume
- ☑️ Fazer o Diplay OLED (conectado à GPIO 14 SDA e GPIO 15 SCL) mostrar o valor do volume constantemente
  
---
<h3>🛠️ Ferramentas</h3>

  - Placa BitDogLab
  - Cabo tipo micro-usb para usb-a
  - Ferramentas CMake e Pico SDK instaladas
---

<h3>🚀 Utilizando o programa</h3>

Siga as etapas a seguir:
  - Pressione o botão "Bootsel" da placa
  - Conecte a placa no computador e solte o botão "Bootsel"
  - Clone o repositório usando o comando abaixo
    
    ```gitconfig
    git clone https://github.com/nevaskab/medidor_sonoro.git
    ```
  - Compile e Rode o código <br>

    ![Captura de tela 2025-01-19 150112](https://github.com/user-attachments/assets/62fbcc03-5653-4826-be75-316d8e6581bb)

  - Pronto! Sua placa, devidamente conectada, será capaz de rodar o código :D <br>

  - Faça barulhos e veja as respostas na matriz de leds 5x5 WS2812 e no display OLED
  - Aperte o botão A ou botão B para testar também
---

<h2>Para mais detalhe sobre o funcionamento...</h2>
Visite: https://drive.google.com/file/d/1dfryXKMeeLUul99ZrfKGh1n9PU_I1CDO/view?usp=sharing

### Autor
---
<a><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/133506658?s=400&u=add96d4ebb6071b0473386091845a1509b3de27b&v=4" width="100px;" alt=""/>
<br />
<sub><b>Andressa Martins</b></sub></a>
