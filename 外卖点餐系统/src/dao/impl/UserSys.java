package dao.impl;



import dao.DAO;
import entity.User;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

//客户id，客户名，性别，密码，送餐地址，手机号，创建时间
public class UserSys implements DAO<User> {
    public static Map<String, User> usermap = new HashMap<>();
    List<User> list = new ArrayList<>();
    Scanner sc = new Scanner(System.in);

    /**
     * 添加客户
     */
    @Override
    public void insert(User t) {
        usermap.put(t.getID(), t);

    }

    /**
     * 查看客户列表
     */
    @Override
    public List<User> findAll() {
        Set<String> keys = usermap.keySet();
        for (String str : keys) {
            list.add(usermap.get(str));
        }
        return list;
    }

    /**
     * 删除指定id的客户
     */
    @Override
    public void delete(String id) {
        if (usermap.get(id) == null) {
            System.out.println("没有当前id的客户");
        } else {
            System.out.println(usermap.get(id) + "已删除！！！");
            usermap.remove(id);
        }

    }

    @Override
    public void addMessage() {

    }

    /**
     * 修改密码（当前登录用户的）
     */
    public void changepwd(String id) {
        User user = findById(id);
        System.out.println("请输入新密码：");
        String str = sc.next();
        User t = new User(user.getID(), user.getUname(), user.getUsex(), str, user.getUadress(), user.getUtel(),
                user.getUtime());
        usermap.put(id, t);

    }

    /**
     * 通过id查找对应客户
     */
    @Override
    public User findById(String id) {
        if (usermap.get(id) == null) {
            return null;
        } else {
            return usermap.get(id);
        }

    }

}