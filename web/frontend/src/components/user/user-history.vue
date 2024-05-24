<template>
    <div>
        <h1 style="text-align: center; color: #37517e; padding-top: 15px;">History</h1>
        <br>
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">#</th>
                    <th scope="col">Date</th>
                    <th scope="col">Voltage</th>
                    <th scope="col">Current</th>
                    <th scope="col">Power</th>
                    <th scope="col">Temperature</th>
                    <th scope="col">Humidity </th>
                    <th scope="col">Lighting </th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="(item, index) in historyData" :key="item._id">
                    <th scope="row">{{ index + 1 + startIndex }}</th>
                    <td>{{ item.formattedDate }}</td>
                    <td>{{ item.voltage }}</td>
                    <td>{{ item.current }}</td>
                    <td>{{ item.power }}</td>
                    <td>{{ item.temperature }}</td>
                    <td>{{ item.humidity }}</td>
                    <td>{{ item.lighting }}</td>
                </tr>
            </tbody>
        </table>

    </div>
</template>
<script>
import moment from 'moment';
import axios from '../../utils/axios-setup';
export default {
    name: 'HistoryView',
    data() {
        return {
            historyData: [],
            startIndex: 0,
        }
    },
    methods: {
        async fetchHistoryData() {
            try {
                const response = await axios.get('/api/history');   
                this.historyData = response.data.map(item => ({
                    voltage: item.voltage,
                    current: item.current,
                    power: item.power,
                    temperature: item.temperature,
                    humidity: item.humidity,
                    lighting: item.lighting,
                    formattedDate: moment(item.Timestamp).format('YYYY-MM-DD HH:mm:ss')
                }));
            } catch (error) {
                console.error(error);
            }
        },
        incrementindextab() {
            return ++this.indextab;
        }
    },
    created() {
        this.fetchHistoryData();
    }

}
</script>