package utils;



import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.type.JavaType;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;


public class Tools{
    //path:json文件路径，class1：集合内元素类型
    //泛型方法：在修饰符和返回值之间添加泛型（<T>）
    public static <T> List<T> getJsonToList(String path,Class class1) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();

        JavaType javaType = objectMapper.getTypeFactory().constructParametricType(List.class,class1);

        List<T> o = (List<T>)objectMapper.readValue(new File(path), javaType);

        return o;
    }

    public static <K,V> Map<K,V> getJsonToMap(String path, Class keyClass, Class valueClass) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();

        JavaType javaType = objectMapper.getTypeFactory().constructParametricType(Map.class,keyClass,valueClass);

        Map<K,V> map = (Map<K,V>)objectMapper.readValue(new File(path), javaType);

        return map;
    }

    public static void writeToJson(String path,Object object) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        objectMapper.writeValue(new File(path),object);

    }
}