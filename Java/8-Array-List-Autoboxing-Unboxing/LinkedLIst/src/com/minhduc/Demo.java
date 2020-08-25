package com.minhduc;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

public class Demo {
    public static void main(String[] args) {
        LinkedList<String> roadToHappy = new LinkedList<String>();

        roadToHappy.add("Go to France");
        roadToHappy.add("Study");
        roadToHappy.add("Come back to Vietnam");
        roadToHappy.add("Have a job");
        roadToHappy.add("Marry Gau");
        roadToHappy.add("Happy forever");

        roadToHappy.add(2, "Apply for an internship");
        roadToHappy.remove(2);
        printList(roadToHappy);

        System.out.println("*****************");

        LinkedList<String> newRoadToHappy = new LinkedList<String>();

        addInOder(newRoadToHappy, "Go to France");
        addInOder(newRoadToHappy, "Study");
        addInOder(newRoadToHappy, "Come back to Vietnam");
        addInOder(newRoadToHappy, "Have a job");
        addInOder(newRoadToHappy, "Marry Gau");
        addInOder(newRoadToHappy, "Happy forever");
        printList(newRoadToHappy);
    }

    public static void printList(LinkedList<String> linkedList) {
        Iterator<String> i = linkedList.iterator();
        int step = 1;
        while (i.hasNext()) {
            System.out.println("Step " + step + ": " + i.next());
            step ++;
        }
    }

    public static boolean addInOder(LinkedList<String> linkedList, String activity) {
        ListIterator<String> stringListIterator = linkedList.listIterator();

        while (stringListIterator.hasNext()) {
            int comparison = stringListIterator.next().compareTo(activity);
            if (comparison > 0) {                   // if activity is smaller than next list element,
                stringListIterator.previous();      // we put the activity right before that element.
                stringListIterator.add(activity);   // for another case, we just move in (on s'en fou)
                return true;
            }
        }
        linkedList.add(activity);
        return true;
    }
}
