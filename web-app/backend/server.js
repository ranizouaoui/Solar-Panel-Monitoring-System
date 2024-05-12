const express = require('express');
const { MongoClient } = require('mongodb')
const cors = require("cors");
const { mqtt_credentials }=require('./api/api');
const app = express();
const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());
const port = 3000;
let uri = "mongodb://root:example@localhost:27017/mydatabase?authSource=admin";

if (process.env.DOCKER_ENV === 'true') {
    uri = "mongodb://root:example@mongodb:27017/mydatabase?authSource=admin";
}
const client = new MongoClient(uri, {useNewUrlParser: true, useUnifiedTopology: true });
const db = client.db('mydatabase');
const collection = db.collection('SolarpanelData');
client.connect().then(() => {
    console.log('Connected to MongoDB')
}).catch(error => {
    console.error(error)
})


var mqtt = require('mqtt')

// initialize the MQTT client

var client1 = mqtt.connect(mqtt_credentials);

// setup the callbacks
client1.on('connect', function () {
    console.log('Connected to hivemq');
});
client1.on('error', function (error) {
    console.log(error);
});

var voltage = [0, 2, 5, 8, 10, 14, 15, 18, 18];
var current = [5, 5, 5, 4.8, 4, 3, 1.5, 0.25, 0];

var mqttdata = {
    temperature: '25',
    humidity: '70',
    power: '16',
    lighting: '25',
    chartData: {
        labels: voltage,
        datasets: [
            {
                label: 'Current-Voltage',
                backgroundColor: '#f87979',
                data: current,
            },
        ],
    },


}
var data_to_store = {
    voltage: 16,
    current: 1,
}

// Subscribe to multiple topics
client1.subscribe(['voltage', 'current', 'power', 'lighting', 'temperature', 'humidity']);
client1.on('message', function (topic, message) {
    // called each time a message is received

    if (topic == 'voltage') {
        voltage.push(parseFloat(message.toString()));
        data_to_store.voltage = parseFloat(message.toString());
    }
    if (topic == 'current') {
        current.push(parseFloat(message.toString()));
        data_to_store.current = parseFloat(message.toString());
    }
    if (topic == 'power') {
        mqttdata.power = message.toString();

    }
    if (topic == 'lighting') {
        mqttdata.lighting = message.toString();
    }
    if (topic == 'temperature') {
        mqttdata.temperature = message.toString();

    }
    if (topic == 'humidity') {
        mqttdata.humidity = message.toString();

    }
});

app.get('/api/pv-data', function (req, res) {
    const currentTime = new Date();
    const data_to_store1 = {
        date: currentTime,
        voltage: data_to_store.voltage,
        current: data_to_store.current,
        power: mqttdata.power,
        lighting: mqttdata.lighting,
        temperature: mqttdata.temperature,
        humidity: mqttdata.humidity,
    }

    console.log(data_to_store1);
    collection.insertOne(data_to_store1)
        .then(result => {
            console.log('Data saved to MongoDB:', result);
            res.send(mqttdata);
        })
        .catch(error => {
            console.error('Error saving data to MongoDB:', error);
            res.status(500).send('Error saving data to MongoDB');
        });

})
app.get('/api/history', async function (req, res) {

    const result = await collection.find().toArray();
    console.log(result);
    res.send(result);
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})