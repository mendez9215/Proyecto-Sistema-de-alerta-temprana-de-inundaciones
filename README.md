# Proyecto-Sistema-de-alerta-temprana-de-inundaciones
Es un proyecto de Industria 4.0 que se realizo para la universidad, es un Sistema de alerta temprana de inundaciones

En este proyecto se utilizo una esp32 programada en arduino para la lectura un sensor de ultrasonido y un DHT11, estos datos son enviados mediante WiFi. Luego se usa node red para recibir estos datos y se separan la cadena de datos enviada según cada variable. Luego en la raspberry se usa Geany para recibir los datos del node red y a su vez enviarlos a la base de datos, en este caso se almacenaron en redis. Luego se realiza la ciencia de datos en python donde se grafican las variables y se crea un csv, a su vez este csv usando el otro codigo de python se puede leer y usa un tkinter para un filtrado y buscar de acuedo a los datos que se requieran. Por ultimo, estos datos se pueden visualizar usando grafana.

NOTA: Los codigo en formato JSON se pueden usar en node red y grafana, solo es importarlos.
