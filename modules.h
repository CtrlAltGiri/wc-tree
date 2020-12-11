#include "discovery.h"
#include <math.h>
int isDivisible(unsigned long int no, LNODE node){

    if(node == NULL)
        return 0;

    unsigned long int x = (unsigned long int)(round((node -> val) * (double)L));
    if(x == no){
        return -1;
    }
    if(x % no == 0)
        return 1;					// different 1 for no is lesser and 2 for x is lesser.
    else if(no % x == 0)
        return 2;

    return 0;
}


void moveNonFactorsRight(NODE traverse, LNODE Ltraverse, NODE newNode, LNODE newNodeL, unsigned long int no){

    while( (traverse && (traverse -> right || traverse -> Lright)) || (Ltraverse && (Ltraverse -> Lright || Ltraverse -> right)) ){
        if(traverse){
            if(traverse -> right){
                if((traverse -> right -> val) % no ){
                    if(newNode)
                        newNode -> right = traverse -> right;
                    else
                        newNodeL -> right = traverse -> right;

                    if(traverse -> right -> right){
                        traverse -> right = traverse -> right -> right;
                        traverse -> Lright = NULL;
                    }
                    else if(traverse -> right -> Lright){
                        traverse -> Lright = traverse -> right -> Lright;
                        traverse -> right = NULL;
                    }
                    else{
                        traverse -> right = NULL;
                        traverse -> Lright = NULL;
                    }

                    if(newNode && newNode -> right){
                        newNode -> right -> right = NULL;
                        newNode -> right -> Lright = NULL;
                    }
                    else if(newNodeL && newNodeL -> right){
                        newNodeL -> right -> right = NULL;
                        newNodeL -> right -> Lright = NULL;
                    }


                    if(newNode)
                        newNode = newNode -> right;
                    else
                        newNode = newNodeL -> right;

                    newNodeL = NULL;
                }
                else
                    traverse = traverse -> right;
                    Ltraverse = NULL;
            }
            else{

                if(!isDivisible(no, traverse -> Lright)){
                    if(newNode)
                        newNode -> Lright = traverse -> Lright;
                    else
                        newNodeL -> Lright = traverse -> Lright;

                    if(traverse -> Lright -> right){
                        traverse -> right = traverse -> Lright -> right;
                        traverse -> Lright = NULL;
                    }
                    else if(traverse -> Lright -> Lright){
                        traverse -> Lright = traverse -> Lright -> Lright;
                        traverse -> right = NULL;
                    }
                    else{
                        traverse -> right = NULL;
                        traverse -> Lright = NULL;
                    }

                    if(newNode && newNode -> Lright){
                        newNode -> Lright -> right = NULL;
                        newNode -> Lright -> Lright = NULL;
                    }
                    else if(newNodeL && newNodeL -> Lright){
                        newNodeL -> Lright -> right = NULL;
                        newNodeL -> Lright -> Lright = NULL;
                    }


                    if(newNode)
                        newNodeL = newNode -> Lright;
                    else
                        newNodeL = newNodeL -> Lright;
                    newNode = NULL;
                }
                else{
                    Ltraverse = traverse -> Lright;
                    traverse = NULL;
                }
            }
        }

        else{
            if(Ltraverse -> right){
                if((Ltraverse -> right -> val) % no ){

                    if(newNode)
                        newNode -> right = Ltraverse -> right;
                    else
                        newNodeL -> right = Ltraverse -> right;

                    if(Ltraverse -> right -> right){
                        Ltraverse -> right = Ltraverse -> right -> right;
                        Ltraverse -> Lright = NULL;
                    }
                    else if(Ltraverse -> right -> Lright){
                        Ltraverse -> Lright = Ltraverse -> right -> Lright;
                        Ltraverse -> right = NULL;
                    }
                    else{
                        Ltraverse -> right = NULL;
                        Ltraverse -> Lright = NULL;
                    }

                    if(newNode && newNode -> right){
                        newNode -> right -> right = NULL;
                        newNode -> right -> Lright = NULL;
                    }
                    else if(newNodeL && newNodeL -> right){
                        newNodeL -> right -> right = NULL;
                        newNodeL -> right -> Lright = NULL;
                    }

                    if(newNode)
                        newNode = newNode -> right;
                    else
                        newNode = newNodeL -> right;

                    newNodeL = NULL;
                }
                else{
                    traverse = Ltraverse -> right;
                    Ltraverse = NULL;
                }
            }

            else{

                if(!isDivisible(no, Ltraverse -> Lright)){

                    if(newNode)
                        newNode -> Lright = Ltraverse -> Lright;
                    else
                        newNodeL -> Lright = Ltraverse -> Lright;

                    if(Ltraverse -> Lright -> right){
                        Ltraverse -> right = Ltraverse -> Lright -> right;
                        Ltraverse -> Lright = NULL;
                    }
                    else if(Ltraverse -> Lright -> Lright){
                        Ltraverse -> Lright = Ltraverse -> Lright -> Lright;
                        Ltraverse -> right = NULL;
                    }
                    else{
                        Ltraverse -> right = NULL;
                        Ltraverse -> Lright = NULL;
                    }

                    if(newNode && newNode -> Lright){
                        newNode -> Lright -> right = NULL;
                        newNode -> Lright -> Lright = NULL;
                    }
                    else if(newNodeL && newNodeL -> Lright){
                        newNodeL -> Lright -> right = NULL;
                        newNodeL -> Lright -> Lright = NULL;
                    }

                    if(newNode)
                        newNodeL = newNode -> Lright;
                    else
                        newNodeL = newNodeL -> Lright;

                    newNode = NULL;
                }
                else{
                    Ltraverse = Ltraverse -> Lright;
                    traverse = NULL;
                }
            }
        }
    }

}


/*	while( (traverse && (traverse -> right || traverse -> Lright)) || (Ltraverse && (Ltraverse -> Lright || Ltraverse -> right)) ){
        if(traverse){
            if(traverse -> right){
                if((traverse -> right -> val) % no ){
                    if(newNode)
                        newNode -> right = traverse -> right;
                    else
                        newNodeL -> right = traverse -> right;

                    if(traverse -> right -> right){
                        traverse -> right = traverse -> right;
                        traverse -> Lright = NULL;
                    }
                    else if(traverse -> right -> Lright){
                        traverse -> Lright = traverse -> right -> Lright;
                        traverse -> right = NULL;
                    }
                    else{
                        traverse -> right = NULL;
                        traverse -> Lright = NULL;
                    }
                    if(newNode){
                        newNode -> right -> right = NULL;
                        newNode -> right -> Lright = NULL;
                    }
                    else{
                        newNodeL -> right -> right = NULL;
                        newNodeL -> right -> Lright = NULL;
                    }

                    if(newNode)
                        newNode = newNode -> right;
                    else
                        newNode = newNodeL -> right;

                    newNodeL = NULL;
                }
                else
                    traverse = traverse -> right;
                    Ltraverse = NULL;
            }
            else{

                if(!isDivisible(no, traverse -> Lright)){
                    if(newNode)
                        newNode -> Lright = traverse -> Lright;
                    else
                        newNodeL -> Lright = traverse -> Lright;

                    if(traverse -> Lright -> right){
                        traverse -> right = traverse -> right;
                        traverse -> Lright = NULL;
                    }
                    else if(traverse -> Lright -> Lright){
                        traverse -> Lright = traverse -> Lright -> Lright;
                        traverse -> right = NULL;
                    }
                    else{
                        traverse -> right = NULL;
                        traverse -> Lright = NULL;
                    }
                    if(newNode){
                        newNode -> Lright -> right = NULL;
                        newNode -> Lright -> Lright = NULL;
                    }
                    else{
                        newNodeL -> Lright -> right = NULL;
                        newNodeL -> Lright -> Lright = NULL;
                    }

                    if(newNode)
                        newNodeL = newNode -> Lright;
                    else
                        newNodeL = newNodeL -> Lright;
                    newNode = NULL;
                }
                else{
                    Ltraverse = traverse -> Lright;
                    traverse = NULL;
                }
            }
        }

        else{
            if(Ltraverse -> right){
                if((Ltraverse -> right -> val) % no ){

                    if(newNode)
                        newNode -> right = traverse -> right;
                    else
                        newNodeL -> right = traverse -> right;

                    if(Ltraverse -> right -> right){
                        Ltraverse -> right = Ltraverse -> right;
                        Ltraverse -> Lright = NULL;
                    }
                    else if(Ltraverse -> right -> Lright){
                        Ltraverse -> Lright = Ltraverse -> right -> Lright;
                        Ltraverse -> right = NULL;
                    }
                    else{
                        Ltraverse -> right = NULL;
                        Ltraverse -> Lright = NULL;
                    }
                    if(newNode){
                        newNode -> right -> right = NULL;
                        newNode -> right -> Lright = NULL;
                    }
                    else{
                        newNodeL -> right -> right = NULL;
                        newNodeL -> right -> Lright = NULL;
                    }

                    if(newNode)
                        newNode = newNode -> right;
                    else
                        newNode = newNodeL -> right;

                    newNodeL = NULL;
                }
                else{
                    traverse = Ltraverse -> right;
                    Ltraverse = NULL;
                }
            }

            else{

                if(!isDivisible(no, Ltraverse -> Lright)){

                    if(newNode)
                        newNode -> Lright = Ltraverse -> Lright;
                    else
                        newNodeL -> Lright = Ltraverse -> Lright;

                    if(Ltraverse -> Lright -> right){
                        Ltraverse -> right = Ltraverse -> right;
                        Ltraverse -> Lright = NULL;
                    }
                    else if(Ltraverse -> Lright -> Lright){
                        Ltraverse -> Lright = Ltraverse -> Lright -> Lright;
                        Ltraverse -> right = NULL;
                    }
                    else{
                        Ltraverse -> right = NULL;
                        Ltraverse -> Lright = NULL;
                    }

                    if(newNode){
                        newNode -> Lright -> right = NULL;
                        newNode -> Lright -> Lright = NULL;
                    }
                    else{
                        newNodeL -> Lright -> right = NULL;
                        newNodeL -> Lright -> Lright = NULL;
                    }

                    if(newNode)
                        newNodeL = newNode -> Lright;
                    else
                        newNodeL = newNodeL -> Lright;

                    newNode = NULL;
                }
                else{
                    Ltraverse = Ltraverse -> Lright;
                    traverse = NULL;
                }
            }
        }
    }*/
