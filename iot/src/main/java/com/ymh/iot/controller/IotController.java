package com.ymh.iot.controller;

import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.ymh.iot.mapper.IotdeviceMapper;
import com.ymh.iot.mapper.LedMapper;
import com.ymh.iot.mapper.ValueMapper;
import com.ymh.iot.pojo.Iotdevice;
import com.ymh.iot.pojo.Led;
import com.ymh.iot.pojo.ReturnMsg.BaseReturnMsg;
import com.ymh.iot.pojo.ReturnMsg.PageReturnMsg;
import com.ymh.iot.pojo.ReturnMsg.ReturnCode;
import com.ymh.iot.pojo.Value;
import com.ymh.iot.serveice.MqttGateway;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Api(tags = "设备管理接口")
@RestController
@RequestMapping(value = "/iot/")
public class IotController {
    @Autowired
    private IotdeviceMapper iotdeviceMapper;
    @Autowired
    private LedMapper ledMapper;
    @Autowired
    private ValueMapper valueMapper;
    @Autowired
    private MqttGateway mqttGateway;

    @ApiOperation(value = "获取所有的led设备")
    @RequestMapping(value = "/led", method = RequestMethod.GET)
    public PageReturnMsg getLedList(@RequestParam("page") int page, @RequestParam("limit") int limit) {
        PageHelper.startPage(page, limit);
        PageReturnMsg msg = new PageReturnMsg();
        PageInfo<Led> pageInfo = new PageInfo<>(ledMapper.getList());
        msg.initMsg(pageInfo);
        return msg;
    }

    @ApiOperation(value = "更改Led状态")
    @RequestMapping(value = "/led/state", method = RequestMethod.PUT)
    public BaseReturnMsg changeLedState(@RequestParam("led") String led, @RequestParam("state") int state) {
        BaseReturnMsg msg = new BaseReturnMsg();
//        System.out.println(led + state);
        ledMapper.changeLedState(led, state);
        mqttGateway.sendToMqtt(led + state, "ymh:desinger");
        msg.setCode(ReturnCode.SUCCESS_REQUEST);
        return msg;
    }

    @ApiOperation(value = "获取所有的设备")
    @RequestMapping(value = "/device", method = RequestMethod.GET)
    public PageReturnMsg getDeviceList(@RequestParam("page") int page, @RequestParam("limit") int limit) {
        PageReturnMsg msg = new PageReturnMsg();
        PageHelper.startPage(page, limit);
        List<Iotdevice> list = iotdeviceMapper.getDevice();
        PageInfo<Iotdevice> pageInfo = new PageInfo<>(list);
        msg.initMsg(pageInfo);
        return msg;
    }


    @ApiOperation(value = "根据设备名称获取最新的100条数据")
    @RequestMapping(value = "/value/{name}",method = RequestMethod.GET)
    public PageReturnMsg getValue(@PathVariable String name){
        PageReturnMsg msg = new PageReturnMsg();
        PageHelper.startPage(1, 100);
        List<Value> list = valueMapper.getValue(name);
        PageInfo<Value> pageInfo = new PageInfo<>(list);
        msg.initMsg(pageInfo);
        return msg;
    }

    @ApiOperation(value = "根据设备名称获取最新的100条数据V")
    @RequestMapping(value = "/value/v/{name}",method = RequestMethod.GET)
    public PageReturnMsg getValueV(@PathVariable String name){
        PageReturnMsg msg = new PageReturnMsg();
        PageHelper.startPage(1, 100);
        List<Integer> list = valueMapper.getValueInt(name);
        PageInfo<Integer> pageInfo = new PageInfo<>(list);
        msg.initMsg(pageInfo);
        return msg;
    }
}
