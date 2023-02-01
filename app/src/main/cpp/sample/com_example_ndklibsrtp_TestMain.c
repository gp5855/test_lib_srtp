//
// Created by GP5855 on 2/1/2023.
//
#include <jni.h>
#include <srtp.h>
#include <string.h>
#include <stdio.h>

JNIEXPORT jint JNICALL
Java_com_example_ndklibsrtp_MainActivity_init(
        JNIEnv* __attribute__((unused)) env,
        jobject __attribute__((unused)) thiz) {

    srtp_t session;
    srtp_policy_t policy;

    uint8_t key[30] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };

    // initialize libSRTP
    srtp_init();

    // default policy values
    memset(&policy, 0x0, sizeof(srtp_policy_t));

    // set policy to describe a policy for an SRTP stream
    srtp_crypto_policy_set_rtp_default(&policy.rtp);
    srtp_crypto_policy_set_rtcp_default(&policy.rtcp);
    srtp_crypto_policy_set_rtcp_default(&policy.rtcp);
    policy.ssrc = (srtp_ssrc_t){ssrc_specific,0};
    policy.key = key;
    policy.next = NULL;

    // allocate and initialize the SRTP session
    srtp_create(&session, &policy);
    // main loop: get rtp packets, send srtp packets
    char rtp_buffer[2048];
    int len;
    rtp_buffer[0] = 'a';
    rtp_buffer[1] = 'b';
    rtp_buffer[2] = 'c';
    rtp_buffer[3] = 'd';
    len = sizeof(rtp_buffer);
    printf("before: %s" ,rtp_buffer);
    srtp_err_status_t status = srtp_protect(session, &rtp_buffer, &len);
    printf("after: %s" ,rtp_buffer);
    status = srtp_unprotect(session,&rtp_buffer,&len);
    printf("after unprotect: %s" ,rtp_buffer);
    return 1;
}
