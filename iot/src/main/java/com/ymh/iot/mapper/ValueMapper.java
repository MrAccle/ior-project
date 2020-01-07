package com.ymh.iot.mapper;

import com.ymh.iot.pojo.Value;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public interface ValueMapper {
    int insert(Value record);

    int insertSelective(Value record);

    @Select("SELECT * FROM `value` where serialId = #{name} ORDER BY id desc")
    List<Value> getValue(@Param("name") String name);

    @Select("SELECT value FROM `value` where serialId = #{name} ORDER BY id desc")
    List<Integer> getValueInt(@Param("name") String name);
}