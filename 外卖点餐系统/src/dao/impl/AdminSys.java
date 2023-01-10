package dao.impl;


import dao.DAO;
import entity.Admin;
import entity.Dishes;
import entity.Order;
import entity.User;
import utils.Tools;

import java.io.IOException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;

import static dao.impl.DishesSys.dishesmap;
import static dao.impl.OrderSys.ordermap;
import static dao.impl.UserSys.usermap;
import java.util.Set;

public class AdminSys implements DAO<Admin> {
    public static Map<String, Admin> map = new HashMap<>();
     static Set<String> keys = map.keySet();
    List<Admin> list = new ArrayList<>();

    UserSys u = new UserSys();
    OrderSys o = new OrderSys();
    DishesSys d = new DishesSys();
    Scanner sc = new Scanner(System.in);

    /**
     * 添加菜品
     */
    public void addDishes() {
        System.out.println("请输入您要添加的菜品:(按照:菜品ID/菜品名/菜品类型/单价/月销量/总数量)");
        String str = sc.next();
        String[] info = str.split("/");
        //
        if (info.length < 6) {
            System.out.println("天啦撸，输入失败啦，请重新输入！");
            addDishes();
        } else {
            LocalDate dtime = LocalDate.now();
            Dishes t = new Dishes(info[0], info[1], info[2], dtime, Double.parseDouble(info[3]),
                    Integer.parseInt(info[4]), Integer.parseInt(info[5]));
            d.insert(t);
            System.out.println("小主,恭喜你！添加成功了");
        }
    }

    /**
     * 查看所有菜品信息(包含分页功能)
     */
    public void showAllDishes(int pageSize) {
        List<Dishes> list = d.findAll();
        int start = 0;
        //先写一个死循环，进入else后break掉
        while (true) {
            if (list.size() > (pageSize + start)) {
                System.out.println(list.subList(start, pageSize + start));

            } else {
                System.out.println(list.subList(start, list.size()));
                break;
            }
            start = start + pageSize;
        }
    }

    /**
     * 查看指定类别的菜品信息
     *
     */
    public void selecBytypeOfAdmin() {
        System.out.println("请输入您要查询菜品的类别：");
        String typename = sc.next();
        d.selectBytype(typename);
    }

    /**
     * 根据菜品id修改菜品价格
     */
    public void selectByDishesID() {
        System.out.println("请输入您要查询的菜品id：");
        String id = sc.next();
        Dishes dish = d.findById(id);
        if (dish == null) {
            System.out.println("没有当前id的菜品呢");
        } else {
            System.out.println("当前菜品为：" + dish);
            System.out.println("请输入新的菜品单价：");
            double newprice = sc.nextDouble();
            Dishes t = new Dishes(dish.getdID(), dish.getDname(), dish.getDtype(), dish.getDtime(), newprice,
                    dish.getDsales(), dish.getDstocks());
            d.insert(t);
            System.out.println("修改成功" + d.findById(t.getdID()));
        }
    }

    /**
     * 删除指定id的菜品
     *
     * //@param args
     */
    public void deleteDishes() {
        System.out.println("请输入您要删除的菜品id");
        String id = sc.next();
        d.delete(id);
        System.out.println("删除成功！！");
    }

    /**
     * 添加客户
     */
    public void addUser() {
        System.out.println("请输入您要添加的用户:按照(id/姓名/性别/密码/送餐地址/手机号)");
        String str = sc.next();
        String[] info = str.split("/");
        if (info.length < 6) {
            System.out.println("您输入的信息有误，请重新输入....");
            addUser();
        } else {
            LocalDateTime utime = LocalDateTime.now();
            u.insert(new User(info[0], info[1], info[2], info[3], info[4], info[5], utime));
            System.out.println("添加成功");
        }
    }

    /**
     * 查看客户列表
     */
    public void findUser() {
        List<User> userlist = u.findAll();
        for (User user : userlist) {
            System.out.println(user);
        }
    }

    /**
     * 根据id查找指定用户
     */
    public User findUserByid(String id) {
        return u.findById(id);
    }

    /**
     * 删除指定id的客户
     */
    public void deleteUserByAdmin() {
        System.out.println("请输入您要删除的id：");
        String id = sc.next();
        u.delete(id);
    }

    /**
     * 订单列表显示
     */
    public void showAllOrder() {
        List<Order> allOrder = o.findAll();
        for (Order order : allOrder) {
            System.out.println(order);
        }
    }

    /**
     * 根据订单id修改订单状态
     */
    public void changeOrderValue() {
        System.out.println("请输入您要修改状态的订单id");
        String id = sc.next();
        Order order = o.findById(id);
        if (order == null) {
            System.out.println("没有当前id的订单，请检查输入");
        } else {
            System.out.println("已找到当前id订单" + order);
            System.out.println("请输入您要修改的状态：0:未支付 1：已支付 2：配送中 3：已完成");
            int value = sc.nextInt();
            Order t = new Order(order.getOrderID(), order.getUtime(), order.getDishes(), order.getOrdernum(),
                    order.getuID(), order.getOrderprice(), value);
            o.insert(t);
            System.out.println("修改成功了！！！");
        }

    }
    /**
     * 显示所有菜品(按菜品销量从高到低排序输出)
     */
    public void showAllDishesByUser() {
        List<Dishes> list = d.findAll();
        Collections.sort(list, (p1, p2) -> p1.getDsales() - p2.getDsales());
        System.out.println(list);
    }

    /**
     * 点餐（输入菜品id和购买数量）
     */
    public void shopDishes(User user) {
        showAllDishesByUser();
        System.out.println("请输入您要购买的id和数量：按照(id/数量)");
        String str = sc.next();
        String[] info = str.split("/");
        // 判断输入是否符合要求，不符合则要求重新输入
        if (info.length < 2) {
            System.out.println("输入有误，请重新输入：");
            shopDishes(user);
        } else {
            LocalDateTime l = LocalDateTime.now();
            // String orderID, LocalDateTime utime, Dishes dishes, int ordernum, String uID,
            // Double orderprice,int orderValue
            Order t = new Order(info[0], l, d.findById(info[0]), Integer.parseInt(info[1]), user.getID(),
                    o.findById(info[0]).getOrderprice(), o.findById(info[0]).getOrderValue());
            o.insert(t);
            System.out.println("订单已生成！！！" + o.findById(info[0]));
        }
    }

    /**
     * 根据菜品类别显示所有菜品
     */
    public void ShowOfTypeByUser() {
        System.out.println("请输入您要查找的类别：");
        String str = sc.next();
        System.out.println(d.findByType(str));

    }

    /**
     * 查看所有订单(当前登录用户的)
     */
    public void showAllOrderByUser(User user) {
        List<Order> list = o.findByuId(user.getID());
        for (Order order : list) {
            System.out.println(order);
        }
    }

    /**
     * 修改密码（当前登录用户的）
     */
    public void changePwdByUser(User user) {
        u.changepwd(user.getID());
        System.out.println("修改成功！！");
    }

    /**
     * 个人信息显示
     */
    public void showByUser(User user) {
        User findById = u.findById(user.getID());
        System.out.println(findById);
    }
    /**
     * 删除管理员
     */
    @Override
    public void delete(String id) {
        if (map.get(id) == null) {
            System.out.println("输入id错误...");
        } else {
            map.remove(id);
        }

    }
    /**
     * 添加管理员
     */
    @Override
    public void insert(Admin t) {
        // TODO Auto-generated method stub
        map.put(t.getID(), t);
    }
    /**
     * 通过id即账号查找管理员
     */
    @Override
    public Admin findById(String id) {
        if (map.get(id) == null) {
            return null;
        } else {
            return map.get(id);
        }
    }
    /**
     * 显示所有管理员
     */
    @Override
    public List<Admin> findAll() {


        for (String key : keys) {
            list.add(map.get(key));
        }
        return list;
    }
    //先设置系统默认数据
    public void addMessage() throws IOException {
        try
        { Admin put = map.put("qwl", new Admin("10086", "qwl", "123456"));

        Tools.writeToJson("Admin.json",map);
 
        LocalDate time = LocalDate.now();
        Dishes d1 = new Dishes("1", "红烧猪蹄", "肉类", time, 12.5, 20, 30);
        d.insert(d1);
        Dishes d2 = new Dishes("2", "鸡公煲", "肉类", time, 21.5, 30, 20);
        d.insert(d2);
        Dishes d3 = new Dishes("3", "麻辣香锅", "火锅类", time, 30, 5, 10);
        d.insert(d3);
        Dishes d4 = new Dishes("4", "水煮肉片", "肉类", time, 15, 12, 15);
        d.insert(d4);
        Dishes d5 = new Dishes("5", "水果沙拉", "水果类", time, 6, 70, 60);
        d.insert(d5);
        Tools.writeToJson("dishes.json",dishesmap);
        // String orderID, LocalDateTime utime, Dishes dishes, int ordernum, String uID,
        // Double orderprice,int orderValue
        LocalDateTime localdatetime = LocalDateTime.now();
        Order o1 = new Order("1", localdatetime, d1, 10, "1001", 60.0, 1);
        o.insert(o1);
        Order o2 = new Order("2", localdatetime, d2, 5, "1002", 50.0, 10);
        o.insert(o2);
        Order o3 = new Order("3", localdatetime, d3, 5, "1003", 40.0, 5);
        o.insert(o3);
        Order o4 = new Order("4", localdatetime, d4, 5, "1004", 30.0, 6);
        o.insert(o4);
        Order o5 = new Order("5", localdatetime, d5, 5, "1005", 20.0, 8);
        o.insert(o5);
        Tools.writeToJson("orders.json",ordermap);
        // String uID, String uname, String usex, String upwd, String uadress, String
        // utel, LocalDateTime utime
        User u1 = new User("1001", "张三", "男", "123456", "湖北", "13545286487", localdatetime);
        u.insert(u1);
        User u2 = new User("1002", "李四", "男", "234567", "湖南", "15927948976", localdatetime);
        u.insert(u2);
        User u3 = new User("1003", "王五", "男", "345678", "江苏", "15927986854", localdatetime);
        u.insert(u3);
        User u4 = new User("1004", "刘柳", "女", "456789", "浙江", "18771580860", localdatetime);
        u.insert(u4);
        User u5 = new User("1005", "赵琦", "女", "567890", "新疆", "18771580750", localdatetime);
        u.insert(u5);
        Tools.writeToJson("users.json",usermap);
        } catch(Exception e) {
        System.out.println("写入文件失败");
    }
    }

}