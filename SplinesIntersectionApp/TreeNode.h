#pragma once
#include <cstdio>

namespace Time {
  static double tA = 0.;
  static double tB = 0.;
  static double dt = 1.;
  static bool m_isSimilarCurve = false;
}

template <class T>
class TreeNode
{
private:
  // ��������� ������ � ������� �������� �����
  TreeNode<T>* left;
  TreeNode<T>* right;

public:
  // �������� �������, ����������� ����������
  T data;

  // ����������� �������������� ���� ������ � ����������
  TreeNode( const T& item, TreeNode<T>* lptr, TreeNode<T>* rptr ) :data( item ), left( lptr ), right( rptr ) {}
  TreeNode( const T& item ) : data( item ) {}
  // ������ ������� � ����� ����������
  TreeNode<T>* Left() const { return left; }
  TreeNode<T>* Right() const { return right; }
  // �������� ����
  void FreeTreeNode( TreeNode<T>* p ) { delete p; }
  // ������������ ����������� ����������� ����� ������
  static void Inorder( TreeNode<T>* a, TreeNode<T>* b, void find( T& itemA, T& itemB ) );
};

template<class T>
void TreeNode<T>::Inorder( TreeNode<T>* a, TreeNode<T>* b, void find( T& itemA, T& itemB ) )
{
  // ����������� ����������� ���������-�� �� ������ ���������
  if ( a == NULL || b == NULL )
    return;

  Time::tA = 0;
  Time::tB = 0;
  if ( a->Left() == NULL || b->Left() == NULL )
    return;
  // �������� ���� ������ ���� ������� ������ � ������ ���� ������� ������
  find( a->Left()->data, b->Left()->data );

  Time::tB += Time::dt;
  Time::m_isSimilarCurve = false;
  find( a->Left()->data, b->Right()->data );

  Time::tA += Time::dt;
  Time::m_isSimilarCurve = false;
  find( a->Right()->data, b->Left()->data );

  Time::tA = Time::tA + Time::dt;
  Time::tB = Time::tB + Time::dt;
  Time::m_isSimilarCurve = false;
  find( a->Right()->data, b->Right()->data );
}

