// axios-setup.js

import axios from 'axios';

const instance = axios.create({
  baseURL: process.env.VUE_AXIOS || 'http://localhost:3000' // Default to localhost
});

export default instance;
