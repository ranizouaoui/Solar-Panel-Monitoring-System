<template>
  <div>
    <div class="input-group rounded" style="padding-top: 18px; width: 93%; margin-left: 14px;">
      <input type="search" class="form-control rounded" placeholder="Enter your city" aria-label="Search"
        aria-describedby="search-addon" />
      <span class="input-group-text border-0" id="search-addon">
        <i class="bi bi-search"></i>
      </span>
    </div>
    <div style="color: white" class="card-1">
      <div class="cards">
        <div class="today1">
          <h3 style="text-align: center;">{{ daily.name }}</h3>

          <div class="daily1">
            <img :src="require(`@/assets/weater_elements/${weathers[daily.weather[0].main]}.svg`)"
              style="width: 170px;" />

            <p style="text-align: center;  font-size: 70px;margin-top: 10%;">{{ parseInt(daily.main.temp) }}°</p>
          </div>
          <h2>{{ daily.weather[0].main }}</h2>
          <br>
          <br>
        </div>
        <div>
          <div class="row" style="height: 20px; --bs-gutter-x: 0rem;">
            <div class="col" style="width: 47px;">
              <div class="wrapper d-flex">
                <img src="@/assets/icons8_wind_50px.png"
                  style="width: 20px; height: 20px; margin-top: 2px; margin-right: 2px;" alt />
                <p> Wind: </p>
              </div>

            </div>
            <div class="col" style="width: 47px;">
              <p>{{ daily.wind.speed }} Km/h</p>
            </div>
            <div class="w-100"></div>
            <div class="col" style="width: 47px;">
              <div class="wrapper d-flex">
                <img src="@/assets/icons8_humidity_50px.png"
                  style="width: 20px; height: 20px; margin-top: 2px;margin-right: 2px;" alt />
                <p> Hum:</p>
              </div>

            </div>
            <div class="col" style="width: 47px;">
              <p>{{ daily.main.humidity }}%</p>
            </div>
          </div>
        </div>

      </div>
      <br>
      <br>

    </div>

    <div class="card-11">
      <div class="row" style="    padding-top: inherit;">
        <div class="col">
          <div class="wrapper d-flex align-items-stretch">
            <img src="@/assets/sun-new.png" style="width: 50px; height: 52px; margin-top: auto; margin-right: 2px;"
              alt />
            <div>
              <h6 style="color: #C3C8DE;">Sunrise</h6>
              <h6 style="color: #5C92FF;"> {{ new Date(this.daily.sys.sunrise * 1000).toLocaleTimeString('en-US') }}
              </h6>
            </div>

          </div>

        </div>
        <div class="col">
          <div class="wrapper d-flex " style="  display: flex;
                        flex-direction: row;
                        align-items: center;
                        justify-content: center;">
            <img src="@/assets/moon.png" style="width: 40px; height: 40Spx; margin-right: 2px;" alt />
            <div>
              <h6 style="color: #C3C8DE;">Sunset </h6>
              <h6 style="color: #5C92FF;"> {{ this.sunset = new Date(this.daily.sys.sunset *
                1000).toLocaleTimeString('en-US') }}</h6>
            </div>
          </div>

        </div>
      </div>


    </div>

  </div>
</template>


<script>
export default {
  name: 'CardsView',
  props: ['daily'],
  data() {
    return {
      weathers: {
        Snow: "snowy",
        Clouds: "cloudy",
        Rain: "rainy",
        Clear: "sunny",
        Thunderstorm: "thunder",
      },
      days: ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'],
      daysIndex: [],

    };
  },
  mounted() {
    var currentDate = new Date();
    var nextWeek = new Date(currentDate.getTime() + 7 * 24 * 60 * 60 * 1000);
    var days = []
    while (currentDate <= nextWeek) {
      days.push(new Date(currentDate).getDay());
      currentDate.setDate(currentDate.getDate() + 1);
    }
    this.daysIndex = days.slice(1);


  },


}

</script>


<style>
.cards {
  display: flex;
  width: 100%;
  margin-top: 3px;
  flex-direction: row;
  justify-content: space-around;
  align-items: center;
  flex-wrap: wrap;
}

.card-1 {
  width: 95%;
  height: 430px;
  background-color: #117ebf;
  border-radius: 10px;
  margin-inline: auto;
  margin-top: 15px;
  padding: 10px;

}

.card-11 {
  width: 100%;
  height: 100px;
  background-color: #fff8f0;
  border-radius: 10px;
  margin-inline: auto;
  border-style: dashed;
  border-color: #ffe4b8;
  border-width: 2px;
  color: #C3C8DE;
  margin-top: 20px;
  padding: 10px;
}

.today1 {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.todayDetails1 {
  display: flex;
  margin-top: 14px;
  align-items: flex-start;
}

.daily1 {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
}
</style>
 