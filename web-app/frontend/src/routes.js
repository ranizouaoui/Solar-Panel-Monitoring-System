import { createRouter, createWebHistory } from 'vue-router';
const routes = [
  {

    path: '/',
    name: 'home',
    component: () => import('./components/static/HomeView')
  },
  {

    path: '/about',
    name: 'about',
    component: () => import('./components/static/AboutView')
  },
  {

    path: '/login',
    name: 'login',
    component: () => import('./components/static/LoginView')
  },
  {
    path: '/services',
    name: 'services',
    component: () => import('./components/static/ServicesView')
  },
  {
    path: '/team',
    name: 'team',
    component: () => import('./components/static/TeamView')
  },
  {
    path: '/contact',
    name: 'contact',
    component: () => import('./components/static/ContactView')
  },
  {
    path: '/pricing',
    name: 'pricing',
    component: () => import('./components/static/PricingView')
  },
  {
    path: '/user',
    name: 'user',
    component: () => import('./components/user/UserView')
  }
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;
