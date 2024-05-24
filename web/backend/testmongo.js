const { MongoClient } = require('mongodb');

const uri = "mongodb+srv://root:example@cluster0.h4x1jxy.mongodb.net/?retryWrites=true&w=majority";
const client = new MongoClient(uri, { useUnifiedTopology: true });

const dbName = 'mydatabase'; // Update with your database name
const collectionName = 'SolarPanelData';

async function saveDataToMongoDB(data) {
    try {
        await client.connect();
        console.log('Connected to MongoDB');

        const db = client.db(dbName);
        const collection = db.collection(collectionName);
        await collection.insertOne(data);

        console.log('Data saved to MongoDB');
    } catch (error) {
        console.error('Error saving data to MongoDB:', error);
    } finally {
        client.close();
        console.log('Disconnected from MongoDB');
    }
}

// Usage example
const dataToSave = { xx: "dzdsd" };
saveDataToMongoDB(dataToSave);
