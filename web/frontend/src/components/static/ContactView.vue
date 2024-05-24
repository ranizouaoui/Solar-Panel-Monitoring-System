<template>
    <div>

        <!-- ======= Contact Section ======= -->
        <section class="contact">
            <div class="container" data-aos="fade-up">

                <div class="section-title">
                    <h2>Contact</h2>
                    <p>Thank you for your interest in <strong>SolPanelMonitor, </strong>. If you have any questions, feedback, or would like to learn more about our services, we would love to hear from you. Please use the contact information provided below, and our dedicated team will get back to you as soon as possible.</p>
                </div>

                <div class="row">

                    <div class="col-lg-5 d-flex align-items-stretch">
                        <div class="info">
                            <div class="address">
                                <i class="bi bi-geo-alt"></i>
                                <h4>Location:</h4>
                                <p>CRTEn : Borj Cedria B.P N°95</p>
                            </div>

                            <div class="email">
                                <i class="bi bi-envelope"></i>
                                <h4>Email:</h4>
                                <p>Admin@Crten.Rnrt.Tn</p>
                            </div>

                            <div class="phone">
                                <i class="bi bi-phone"></i>
                                <h4>Call:</h4>
                                <p>79 325 811 / 79 325 215</p>
                            </div>

                            <iframe
                                src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3198.2351661933!2d10.42441621088341!3d36.716912972155306!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x12fd4e31fb2afa53%3A0x8ff90b6a192dbc6e!2sCentre%20De%20Recherches%20Et%20Des%20Technologies%20De%20L&#39;%C3%A9nergie%20(CRTEn)!5e0!3m2!1sfr!2stn!4v1714848285583!5m2!1sfr!2stn"
                                frameborder="0" style="border:0; width: 100%; height: 290px;" allowfullscreen></iframe>

                        </div>

                    </div>

                    <div class="col-lg-7 mt-5 mt-lg-0 d-flex align-items-stretch">
                        <form action="forms/contact.php" method="post" role="form" class="php-email-form">
                            <div class="row">
                                <div class="form-group col-md-6">
                                    <label for="name">Your Name</label>
                                    <input type="text" name="name" class="form-control" id="name" required>
                                </div>
                                <div class="form-group col-md-6">
                                    <label for="name">Your Email</label>
                                    <input type="email" class="form-control" name="email" id="email" required>
                                </div>
                            </div>
                            <div class="form-group">
                                <label for="name">Subject</label>
                                <input type="text" class="form-control" name="subject" id="subject" required>
                            </div>
                            <div class="form-group">
                                <label for="name">Message</label>
                                <textarea class="form-control" name="message" rows="10" required></textarea>
                            </div>
                            <div class="my-3">
                                <div class="loading">Loading</div>
                                <div class="error-message"></div>
                                <div class="sent-message">Your message has been sent. Thank you!</div>
                            </div>
                            <div class="text-center"><button type="submit">Send Message</button></div>
                        </form>
                    </div>

                </div>

            </div>
        </section><!-- End Contact Section -->
    </div>
</template>
<script>
export default {
    name: 'ContactView',
    data() {
        return {

        }
    },
}
</script>