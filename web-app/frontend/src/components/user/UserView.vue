<template>
    <div>
        <div class="container-fluid">
            <div class="row flex-nowrap">
                <div class="col-auto col-md-3 col-xl-2 px-sm-2 px-0 bg-light">
                    <sidebar @item-clicked="handleSidebarItemClick"></sidebar>
                </div>
                <div class="col py-3">
                    <component :is="activeItemComponent"></component>
                </div>
            </div>
        </div>
    </div>
</template>
<script>
import Sidebar from '../layout/SideBarView.vue';
import Component1 from './user-homeView.vue';
import Component2 from './user-history.vue';
export default {
    name: 'UserView',
    components: { Sidebar, Component1, Component2 },
    data() {
        return {
            activeItemComponent: Component1,

        }

    },
    methods: {
        handleSidebarItemClick(item) {
            // Set the selected component based on the clicked sidebar item
            switch (item) {
                case 1:
                    this.activeItemComponent = Component1;
                    break;
                case 2:
                    this.activeItemComponent = Component2;
                    break;
                default:
                    this.activeItemComponent = null;
            }
        }
    }
}
</script>
<style >
.nav-link {
    color: #000000;
}
</style>./layout/SideBarView.vue./user/user-history.vue./user/user-homeView.vue