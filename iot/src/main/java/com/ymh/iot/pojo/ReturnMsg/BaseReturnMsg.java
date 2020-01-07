package com.ymh.iot.pojo.ReturnMsg;

public class BaseReturnMsg {
    private boolean success = false;
    private int code;
    private String msg;
    private Object data;

    public int getCode() {
        return code;
    }


    public void setCode(ReturnCode code){
        this.setCode(code.getCode());
        this.setMsg(code.getMsg());
        if(code == ReturnCode.SUCCESS_REQUEST){
            this.success = true;
        }else {
            this.success = false;
        }
    }

    public void setCode(ReturnCode code,boolean success) {
        this.setCode(code.getCode());
        this.setMsg(code.getMsg());
        this.success = success;
    }

    public boolean isSuccess() {
        return success;
    }

    public void setSuccess(boolean success) {
        this.success = success;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data = data;
    }
}
