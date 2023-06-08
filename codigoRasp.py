import paho.mqtt.client as mqtt
import redis
import time

r = redis.Redis(
host ='redis-10258.c60.us-west-1-2.ec2.cloud.redislabs.com',
port=10258,
password='BYKu0Y2n4cNsBqIrGEO8kDwUhBbhYNR6')

# Variables para almacenar los datos
temperatura = ""
humedad = ""
distancia = ""

# Función de callback que se ejecuta cuando se recibe un mensaje MQTT
def on_message(client, userdata, msg):
    global temperatura, humedad, distancia

    # Obtener el mensaje y el tema del canal
    mensaje = msg.payload.decode()
    tema = msg.topic
    
    try:
        valor = float(mensaje)
    except ValueError:
        print(f"Error: el valor recibido en el tema '{tema}' no es numérico")
        return
    # Guardar los datos en Redis
    #r.set(tema, valor)
    ts = r.ts()
    #ts.create("temperatura")
    #ts.create("humedad")
    #ts.create("distancia")

    # Actualizar las variables de datos
    if tema == "temperatura":
        temperatura = valor
        ts.add("temperatura", "*", temperatura)
    elif tema == "humedad":
        humedad = valor
        ts.add("humedad", "*", humedad)
    elif tema == "distancia":
        distancia = valor
        ts.add("distancia", "*", distancia)

    # Imprimir los datos en pantalla
    print("Temperatura:", temperatura)
    print("Humedad:", humedad)
    print("Distancia:", distancia)
    print("")

# Configuración del cliente MQTT
broker_address = "broker.mqttdashboard.com"  # Dirección IP o nombre de dominio del broker MQTT
client = mqtt.Client()
client.on_message = on_message

# Conexión al broker MQTT y suscripción a los canales
client.connect(broker_address)
client.subscribe("temperatura")
client.subscribe("humedad")
client.subscribe("distancia")

# Loop principal para mantener la conexión y procesar los mensajes entrantes
client.loop_start()

# Mantener el bucle principal mientras se envían los datos a Redis
try:
    while True:
        pass
        # Realizar otras operaciones o análisis con los datos recibidos, si es necesario
        # Por ejemplo, puedes acceder a los datos de Redis y realizar cálculos o enviarlos a otra plataforma

        # Esperar un intervalo antes de realizar la siguiente operación
        # Esto evita un uso excesivo de recursos del procesador
        #time.sleep(0.1)
        #print("Datos: ")

except KeyboardInterrupt:
    # Detener el bucle y desconectar del broker MQTT al recibir una interrupción del teclado (Ctrl+C)
    client.loop_stop()
    client.disconnect()
