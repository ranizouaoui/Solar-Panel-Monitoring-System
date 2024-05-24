<template>
    <div class="container mt-5">
        <h2 class="mb-4">Modifier le profil</h2>
        <form @submit.prevent="updateProfile">
            <div class="mb-3">
                <label for="email" class="form-label">Adresse e-mail :</label>
                <input v-model="email" type="email" class="form-control" id="email" required />
            </div>

            <div class="mb-3">
                <label for="username" class="form-label">Nom d'utilisateur :</label>
                <input v-model="username" type="text" class="form-control" id="username" required />
            </div>

            <div class="mb-3">
                <label for="password" class="form-label">Mot de passe :</label>
                <input v-model="password" type="password" class="form-control" id="password" />
            </div>

            <div class="mb-3">
                <label for="phoneNumber" class="form-label">Numéro de téléphone :</label>
                <input v-model="phoneNumber" type="tel" class="form-control" id="phoneNumber" />
            </div>

            <div class="mb-3">
                <label for="note" class="form-label">Remarque :</label>
                <textarea v-model="note" class="form-control" id="note"></textarea>
            </div>

            <button type="submit" class="btn btn-primary">Mettre à jour le profil</button>
        </form>
    </div>
</template>


<script>
import "../../utils/firebase";
import {
    getAuth,
    updateEmail,
    updatePassword,
    reauthenticateWithCredential,
    EmailAuthProvider,
} from 'firebase/auth';
import { getFirestore,query,collection, onSnapshot } from 'firebase/firestore';


const db = getFirestore();
const q = query(collection(db, "users"));

export default {
    name:"ProfileView",
    data() {
        return {
            email: '',
            username: '',
            password: '',
            phoneNumber: '',
            note: '',
            uid:localStorage.getItem("uidUser"),
        };
    },
    async created() {
        onSnapshot(q, (querySnapshot) => {
            querySnapshot.forEach((doc) => {
                if (doc.data().uid == this.uid) {
                this.email = doc.data().email;
                this.username = doc.data().name;
                this.phoneNumber = doc.data().phone;
                }
            });
        });
    },
    methods: {
          async updateProfile() {
  const auth = getAuth();
  const user = auth.currentUser;

  if (user) {
    try {
      // Reauthenticate the user by prompting for their password
      const password = prompt('Please enter your password to confirm the changes.');
      const credentials = EmailAuthProvider.credential(user.email, password);

      // Reauthenticate the user
      await reauthenticateWithCredential(user, credentials);

      // Update user credentials
      if (this.email) await updateEmail(user, this.email);
      if (this.password) await updatePassword(user, this.password);


      console.log('Profile updated successfully!');
    } catch (error) {
      console.error('Error updating profile:', error.message);
    }
  }
},

    },
};
</script>

<style scoped>
/* Add your component styles here */
</style>