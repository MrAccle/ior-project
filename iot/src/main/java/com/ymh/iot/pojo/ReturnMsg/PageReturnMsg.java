package com.ymh.iot.pojo.ReturnMsg;

import com.github.pagehelper.PageInfo;

public class PageReturnMsg extends BaseReturnMsg{
    private Long total;
    private int pageNum;
    private int pageSize;
    private int size;

    public void initMsg(PageInfo info){
        this.setCode(ReturnCode.SUCCESS_REQUEST,true);
        this.setData(info.getList());
        this.setPageNum(info.getPageNum());
        this.setPageSize(info.getPageSize());
        this.setSize(info.getSize());
        this.setTotal(info.getTotal());
    }

    public Long getTotal() {
        return total;
    }

    public void setTotal(Long total) {
        this.total = total;
    }

    public int getPageNum() {
        return pageNum;
    }

    public void setPageNum(int pageNum) {
        this.pageNum = pageNum;
    }

    public int getPageSize() {
        return pageSize;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }
}
