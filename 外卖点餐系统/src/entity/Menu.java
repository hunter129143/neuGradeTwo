package entity;



import dao.impl.AdminSys;
import entity.User;

import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class Menu {
    static AdminSys admin = new AdminSys();
    Scanner sc = new Scanner(System.in);

    public void showMenu() throws IOException {
        admin.addMessage();

        System.out.println("请输入账号和密码：按照(账号/密码)");
        String str = sc.next();
        String[] info = str.split("/");
        if (info.length < 2) {
            System.out.println("输入有误，请重新输入：");
            showMenu();
        } else {
            if (admin.findById(info[0]) != null && Objects.equals(admin.findById(info[0]).getpwd(), info[1])) {
                adminMenu();
            } else if (admin.findUserByid(info[0]) != null
                    && Objects.equals(info[1], admin.findUserByid(info[0]).getpwd())) {
                User user = admin.findUserByid(info[0]);
                userMenu(user);
            } else {
                System.out.println("输入有误，请重新输入....");
                showMenu();
            }
        }

    }

    public void userMenu(User user) {
        System.out.println("=========欢迎来到订餐系统=======");
        System.out.println("====【1】点餐=================");
        System.out.println("====【2】根据菜品类别显示所有菜品===");
        System.out.println("====【3】查看所有订单============");
        System.out.println("====【4】修改密码===============");
        System.out.println("====【5】个人信息显示============");
        System.out.println("====【6】退出==================");
        System.out.println("请输入您要进行的操作：");
        String n = sc.next();
        switch (n) {
            case "1":
                admin.shopDishes(user);
                userMenu(user);
                break;
            case "2":
                admin.ShowOfTypeByUser();
                userMenu(user);
                break;
            case "3":
                admin.showAllOrderByUser(user);
                userMenu(user);
                break;
            case "4":
                admin.changePwdByUser(user);
                userMenu(user);
                break;
            case "5":
                admin.showByUser(user);
                userMenu(user);
                break;
            case "6":
                System.out.println("谢谢使用，再见！");
                System.exit(0);
            default:
                System.out.println("输入错误，请重新输入：");
                userMenu(user);
        }
    }

    public void adminMenu() {
        System.out.println("=========欢迎您尊贵的管理员=======");
        System.out.println("====【1】添加菜品===============");
        System.out.println("====【2】查看所有菜品信息显示=======");
        System.out.println("====【3】查看指定类别的菜品信息=====");
        System.out.println("====【4】根据菜品id修改菜品价格=====");
        System.out.println("====【5】删除指定id的菜品=========");
        System.out.println("====【6】添加客户================");
        System.out.println("====【7】查看客户列表=============");
        System.out.println("====【8】删除指定id的用户==========");
        System.out.println("====【9】订单列表显示=============");
        System.out.println("====【10】根据订单id修改订单状态====");
        System.out.println("====【11】退出=================");
        String m = sc.next();
        switch (m) {
            case "1":
                admin.addDishes();
                adminMenu();
                break;
            case "2":
                System.out.println("请输入您需要每行显示多少数据：");
                int pageSize = sc.nextInt();
                admin.showAllDishes(pageSize);
                adminMenu();
                break;
            case "3":
                admin.selecBytypeOfAdmin();
                adminMenu();
                break;
            case "4":
                admin.selectByDishesID();
                adminMenu();
                break;
            case "5":
                admin.deleteDishes();
                adminMenu();
                break;
            case "6":
                admin.addUser();
                adminMenu();
                break;
            case "7":
                admin.findUser();
                adminMenu();
                break;
            case "8":
                admin.deleteUserByAdmin();
                adminMenu();
                break;
            case "9":
                admin.showAllOrder();
                adminMenu();
                break;
            case "10":
                admin.changeOrderValue();
                adminMenu();
                break;
            case "11":
                System.out.println("谢谢使用，再见！");
                System.exit(0);
                break;
            default:
                System.out.println("输入错误，请重新输入：");
                adminMenu();
        }
    }
}