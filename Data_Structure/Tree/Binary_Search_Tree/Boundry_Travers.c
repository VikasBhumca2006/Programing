
void traverse_Leaf ( Tree * root )
{
	if ( NULL == root )
		return;

	if ( ( NULL == root->left ) && ( NULL == root->right ) )
		printf (" %d ",root->data );

}

void traverse_Left ( Tree * root )
{
	//if ( NULL == root->left && )
	if ( ( NULL == root->left ) && ( NULL == root->right ) )
		return;

	printf (" %d ",root->data );

	traverse_Left ( root->left );
}

void traverse_Right ( Tree * root )
{
	//if ( NULL == root->right )
	if ( ( NULL == root->left ) && ( NULL == root->right ) )
		return;


	traverse_Right ( root->right );

	printf (" %d ",root->data );
}


void Boundry_Travers ( Tree * root ) 
{
	if ( NULL == root )
		return;

	printf (" %d ",root->data );

	if ( root->left )
		traverse_Left ( root->left );

	traverse_Leaf ( root );

	if ( root->right )
		traverse_Right ( root->right );
}
