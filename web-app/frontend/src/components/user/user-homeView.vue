<template>
    <div>
        <div class="container-fluid">
            <div class="row flex-nowrap">

                <div class="col">
                    <br>
                    <div class="card-group" style="display: grid;">
                        <div class="row row-cols-1 row-cols-md-3 g-4">
                            <div class="col-7">
                                <div class="card text-bg-primary text-center">

                                    <div class="card-body">
                                        <div class="wrapper d-flex align-items-end" style="justify-content: center;">
                                            <i class="bi bi-thermometer-sun fs-2"></i>
                                            <h3 class="card-title">Temperature</h3>
                                        </div>

                                        <h2 class="card-title">{{ data.temperature }}°</h2>
                                    </div>
                                </div>
                            </div>
                            <div class="col">
                                <div class="card text-bg-danger text-center">

                                    <div class="card-body">
                                        <div class="wrapper d-flex align-items-end" style="justify-content: center;">
                                            <i class="bi bi-brightness-high fs-2" style="padding-right: 8px;"></i>
                                            <h3 class="card-title">Lighting</h3>
                                        </div>

                                        <h2 class="card-title">{{ data.lighting }} Lux</h2>
                                    </div>
                                </div>
                            </div>
                            <div class="col">
                                <div class="card text-bg-warning text-center">

                                    <div class="card-body">
                                        <div class="wrapper d-flex align-items-end" style="justify-content: center;">
                                            <i class="bi bi-thermometer-snow fs-2"></i>
                                            <h3 class="card-title">Humidity</h3>
                                        </div>

                                        <h2 class="card-title">{{ data.humidity }}%</h2>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <br>
                    <!-- <div class="d-grid gap-2">
                        <h2 style="text-align: center;">Pump</h2>
                        <button class="btn btn-success" @click="turnOn" type="button">On</button>
                        <button class="btn btn-danger" @click="turnOff" type="button">Off</button>
                    </div> -->
                    <br>
                    <Line :key="chartKey" v-if="loaded" :options="chartOptions" :data="chartData" />
                </div>
                <div class="col-4">
                    <DailyCard v-if="dailyData" :daily="dailyData" />
                </div>
            </div>
        </div>
    </div>
</template>
<script>
import {
    Chart as ChartJS,
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
} from 'chart.js'
import { Line } from 'vue-chartjs'
ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
)
import DailyCard from '../layout/CardsView.vue'
import axios from '../../utils/axios-setup';
export default {
    name: 'UserView',
    components: { DailyCard, Line },
    data() {
        return {
            dailyData: null
            ,
            data: {
                temperature: 0,
                humidity: 0,
                lighting: 0,
            },
            chartOptions: {
                responsive: true,
            },
            chartData: {
                labels: [0],
                datasets: [
                    {
                        label: 'Current-Voltage',
                        backgroundColor: '#f87979',
                        data: [0],
                    },
                ],
            },
            loaded: false,
            chartKey: 0,
        };
    },
    methods: {
        //With Geolocation

        async getWeatherdate() {
            const city = "ben arous"
            const weatherApiUrl = `https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=20571ab45c74dc2a1897b60c5b8047a1`;
            const response = await axios.get(weatherApiUrl);
            this.dailyData = response.data;
        },

        // turnOn() {
        //     this.sendCommand(1);
        // },
        // turnOff() {
        //     this.sendCommand(0);
        // },
        // async sendCommand(value) {
        //     const response = await axios.post('http://localhost:3000/api/pumpe', { command: value })
        //     console.log(response);

        // },
        // Get User Location 


        async fetchDataFromAPI() {
            try {
                // Make API request to fetch position data
                const data1 = await axios.get('/api/pv-data');
                const NewData = data1.data;
                //console.log(NewData);
                this.data.temperature = NewData.temperature;
                this.data.humidity = NewData.humidity;
                this.data.lighting = NewData.lighting;
                //  this.data.current[5](NewData.current);
                //  this.data.voltage.push(NewData.voltage);
                this.loaded = true
                console.log(NewData.chartData);
                this.chartData.labels = NewData.chartData.labels;
                this.chartData.datasets[0].data = NewData.chartData.datasets[0].data;
                this.chartKey++;

            } catch (error) {
                console.error("Error fetching  data:", error);
            }

        }

    },
    created() {
        this.getWeatherdate()
        this.fetchDataFromAPI()
        // Fetch data every 2 seconds
        setInterval(() => {
            this.fetchDataFromAPI();
        }, 5000);



    }
}
</script>
<style >
.nav-link {
    color: #000000;
}
</style>../../utils/axios-setup./CardsView.vue