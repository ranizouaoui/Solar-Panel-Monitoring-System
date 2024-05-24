<template>
  <!-- Navbar -->
  <!-- ======= Header ======= -->
  <!-- ======= Header ======= -->
  <header id="header">
    <div class="container d-flex align-items-center">

      <h1 class="logo me-auto"><a>SolPanelMonitor</a></h1>
      <!-- Uncomment below if you prefer to use an image logo -->
      <!-- <a href="index.html" class="logo me-auto"><img src="assets/img/logo.png" alt="" class="img-fluid"></a>-->

      <nav id="navbar" class="navbar">
        <ul>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link active" to="/">Home</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link" to="/about">About</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link" to="/services">Services</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link" to="/team">Team</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link" to="/pricing">Pricing</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link" to="/contact">Contact</router-link></li>
          <li><router-link v-if="CheckAuth1 == null" class="nav-link getstarted" to="/login">Get Started</router-link></li>
          <li class="nav-item"><a class="nav-link" style="cursor: pointer" v-if="CheckAuth1" @click="logout" ><i class="fs-4 bi-box-arrow-right" style="padding-right: 5px;"></i> Logout</a>
              </li>
        </ul>
        <i class="bi bi-list mobile-nav-toggle"></i>
      </nav><!-- .navbar -->

    </div>
  </header><!-- End Header -->

  <!-- Navbar -->
  <router-view />
</template>
<script>import "../../utils/firebase";
import router from "../../routes";
import { getAuth, signOut, onAuthStateChanged } from "firebase/auth";
const auth = getAuth();
export default {
  name: "NavbarView",
  data() {
    return {
       CheckAuth1:null,
    }

  },
  methods: {
     logout() {
      signOut(auth)
        .then(() => {
          localStorage.removeItem("uidUser");
           router.push("/");
        })
        .catch((error) => {
          console.log(error);
        });
    },

  },
  mounted() {


  },
    beforeCreate() {
    onAuthStateChanged(auth, (user) => {
       this.loading = true;
      if (user) {
        this.CheckAuth1 = user;
      } else {
        this.CheckAuth1 = null;
      }
        this.loading = false;
    },
     );

  }

};

</script>
<style></style>
