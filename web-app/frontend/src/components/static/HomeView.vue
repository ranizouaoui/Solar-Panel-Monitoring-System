<template>
  <div>
    <!-- ======= Hero Section ======= -->
    <section id="hero" class="d-flex align-items-center">

      <div class="container">
        <div class="row">
          <div class="col-lg-6 d-flex flex-column justify-content-center pt-4 pt-lg-0 order-2 order-lg-1"
            data-aos="fade-up" data-aos-delay="200">
            <h1>Unleash solar power at your fingertips.</h1>
            <h2> Empower your energy future with real-time solar panel monitoring. Harness the power of the sun and take
              control of your energy generation like never before. Illuminate your path to a sustainable future with our
              innovative solar panel control app.</h2>
            <div class="d-flex justify-content-center justify-content-lg-start">
              <!-- <a class="btn-get-started">Get Started</a> -->
              <router-link class="nav-link btn-get-started" to="/login">Get Started</router-link>
            </div>
          </div>
          <div class="col-lg-6 order-1 order-lg-2 hero-img" data-aos="zoom-in" data-aos-delay="200">
            <img src="@/assets/pv1.png" class="img-fluid animated" alt=""
              style="width: 70%;height: 98%;padding-bottom: 2%;margin-left: 20%;">
          </div>
        </div>
      </div>

    </section><!-- End Hero -->
    <!-- ======= Clients Section ======= -->
    <section id="clients" class="clients section-bg">
      <div class="container">

        <div class="row" data-aos="zoom-in">

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-7.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-2.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-3.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-4.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-5.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-6.png" class="img-fluid" alt="">
          </div>

        </div>

      </div>
    </section>
    <AboutView></AboutView>
    <ServicesView></ServicesView>
    <TeamView></TeamView>
    <PricingView></PricingView>
    <ContactView></ContactView>
  </div>

  <footer class="container">
    <p>&copy; Copy-rights 2023</p>
  </footer>
</template>
<script>
import AboutView from "./AboutView";
import ContactView from "./ContactView";
import PricingView from "./PricingView";
import ServicesView from "./ServicesView";
import TeamView from "./TeamView.vue";
export default {
  name: 'HomeView',
  components: {
    AboutView, ContactView, PricingView, ServicesView, TeamView

  }
}
</script>

<style></style>
 