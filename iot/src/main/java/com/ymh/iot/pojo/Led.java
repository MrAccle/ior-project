package com.ymh.iot.pojo;

public class Led {
    private String led;

    private Integer state;

    public String getLed() {
        return led;
    }

    public void setLed(String led) {
        this.led = led == null ? null : led.trim();
    }

    public Integer getState() {
        return state;
    }

    public void setState(Integer state) {
        this.state = state;
    }
}